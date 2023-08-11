use apng::{load_dynamic_image, Encoder, Frame, PNGImage};
use plotters::prelude::*;
use std::fs::File;
use std::io::{BufWriter, Read};
use std::path::Path;
use rand::prelude::*;

mod kd_tree;
mod verlet_integration;

#[allow(dead_code)]
fn draw_graph(i: usize, vec1: &kd_tree::Points2D) {
    let out_file_name = format!("{:04}", i).to_string() + ".png";

    let root = BitMapBackend::new(&out_file_name, (2560, 1440)).into_drawing_area();

    root.fill(&BLACK).unwrap();

    let scale = 1.0;

    let mut chart = ChartBuilder::on(&root)
        //.caption("y=x^2", ("sans-serif", 50).into_font())
        .margin(5)
        .x_label_area_size(30)
        .y_label_area_size(30)
        .build_cartesian_2d((-2.56 * scale)..(2.56 * scale), (-1.44 * scale)..(1.44 * scale))
        .unwrap();

    chart.configure_mesh().draw().unwrap();

    chart
    .draw_series(PointSeries::of_element(
        (0..vec1.points.len()).map(|i| (vec1.points[i].x, vec1.points[i].y)),
        1,
        ShapeStyle::from(&WHITE).filled(),
        &|coord, size, style| EmptyElement::at(coord) + Circle::new((0, 0), size, style),
    ))
    .unwrap();

    root.present().unwrap();
}

#[allow(dead_code)]
fn gen_apng(num: usize) {
    let mut files = vec![];

    for i in 0..num {
        files.push(format!("{:04}", i).to_string() + ".png");
    }

    let mut png_images: Vec<PNGImage> = Vec::new();

    for f in files.iter() {
        let mut file = File::open(f).unwrap();
        let mut buffer = vec![];
        file.read_to_end(&mut buffer).unwrap();
        let img = image::load_from_memory(&buffer).unwrap();
        png_images.push(load_dynamic_image(img).unwrap());
    }

    let path = Path::new(r"graph.png");
    let mut out = BufWriter::new(File::create(path).unwrap());

    let config = apng::create_config(&png_images, None).unwrap();
    let mut encoder = Encoder::new(&mut out, config).unwrap();

    for image in png_images.iter() {
        let frame = Frame {
            delay_num: Some(1),
            delay_den: Some(20),
            ..Default::default()
        };
        encoder.write_frame(image, frame).unwrap();
    }

    match encoder.finish_encode() {
        Ok(_n) => println!("success"),
        Err(err) => eprintln!("{}", err),
    }
}

fn main() {
    let seed: [u8; 32] = [1; 32];
    let mut rng: rand::rngs::StdRng = rand::SeedableRng::from_seed(seed);

    let num_point: usize = 25_000;

    let mut n_body = verlet_integration::VerletIntegration::new();
    n_body.epsilon = 1.0e-1;
    n_body.dt = 1.0e-5;
    n_body.radius = 1.0;

    loop {
        let x1_r = 1.0 * 2.0 * (rng.gen::<f64>() - 0.5);
        let y1_r = 0.7 * 2.0 * (rng.gen::<f64>() - 0.5);
        let v = 1.0 / (x1_r * x1_r + y1_r * y1_r + n_body.epsilon * n_body.epsilon).sqrt();
        let x2_r = x1_r - 1.0e2 * v * n_body.dt * y1_r;
        let y2_r = y1_r + 1.0e2 * v * n_body.dt * x1_r;
        if x1_r * x1_r + y1_r * y1_r < 0.7 * 0.7 {
            n_body.vec2.points.push(kd_tree::Grid2D { x: x2_r, y: y2_r });
            n_body.vec3.points.push(kd_tree::Grid2D { x: x1_r, y: y1_r });
        }
        if n_body.vec2.points.len() == num_point {
            break;
        }
    }

    for _ in 0..n_body.vec2.points.len() {
        n_body.vec1.points.push(kd_tree::Grid2D { x: 0.0, y: 0.0 });
    }

    let max_counter = 12000;
    let interval = 1;

    for i in 0..max_counter {
        draw_graph(i, &n_body.vec2);
        for _ in 0..interval {
            n_body.verlet_integration();
            //n_body.verlet_integration_divide();
        }
        println!("{} / {}", i, max_counter - 1);
    }

    gen_apng(max_counter);
}
