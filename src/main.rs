use plotters::prelude::*;

mod embedded_runge_kutta;

#[allow(dead_code)]
fn three_body(vec: &Vec<f64>) -> Vec<f64> {
    let mut ret = vec.clone();
    let r04 = ((vec[0] - vec[4]) * (vec[0] - vec[4]) + (vec[1] - vec[5]) * (vec[1] - vec[5])).sqrt();
    let r08 = ((vec[0] - vec[8]) * (vec[0] - vec[8]) + (vec[1] - vec[9]) * (vec[1] - vec[9])).sqrt();
    let r48 = ((vec[4] - vec[8]) * (vec[4] - vec[8]) + (vec[5] - vec[9]) * (vec[5] - vec[9])).sqrt();
    let r04_3 = r04 * r04 * r04;
    let r08_3 = r08 * r08 * r08;
    let r48_3 = r48 * r48 * r48;
    ret[0]  = vec[2];
    ret[1]  = vec[3];
    ret[2]  = - 5.0 * (vec[0] - vec[4]) / r04_3
              - 3.0 * (vec[0] - vec[8]) / r08_3;
    ret[3]  = - 5.0 * (vec[1] - vec[5]) / r04_3
              - 3.0 * (vec[1] - vec[9]) / r08_3;
    ret[4]  = vec[6];
    ret[5]  = vec[7];
    ret[6]  = - 4.0 * (vec[4] - vec[0]) / r04_3
              - 3.0 * (vec[4] - vec[8]) / r48_3;
    ret[7]  = - 4.0 * (vec[5] - vec[1]) / r04_3
              - 3.0 * (vec[5] - vec[9]) / r48_3;
    ret[8]  = vec[10];
    ret[9]  = vec[11];
    ret[10] = - 4.0 * (vec[8] - vec[0]) / r08_3
              - 5.0 * (vec[8] - vec[4]) / r48_3;
    ret[11] = - 4.0 * (vec[9] - vec[1]) / r08_3
              - 5.0 * (vec[9] - vec[5]) / r48_3;
    ret
}

#[allow(dead_code)]
fn draw(time: f64, n1x: &Vec<f64>, n1y: &Vec<f64>, n2x: &Vec<f64>, n2y: &Vec<f64>, n3x: &Vec<f64>, n3y: &Vec<f64>) {
    let file_name = (time as i32).to_string() + ".png";
    let caption = ((time - 10.0) as i32).to_string() + " - " + &(time as i32).to_string();
    let graph_margin = 0.5;

    let n1x_max = n1x.iter().fold(0.0 / 0.0, |m, v| v.max(m));
    let n1x_min = n1x.iter().fold(0.0 / 0.0, |m, v| v.min(m));
    let n1y_max = n1y.iter().fold(0.0 / 0.0, |m, v| v.max(m));
    let n1y_min = n1y.iter().fold(0.0 / 0.0, |m, v| v.min(m));

    let n2x_max = n2x.iter().fold(0.0 / 0.0, |m, v| v.max(m));
    let n2x_min = n2x.iter().fold(0.0 / 0.0, |m, v| v.min(m));
    let n2y_max = n2y.iter().fold(0.0 / 0.0, |m, v| v.max(m));
    let n2y_min = n2y.iter().fold(0.0 / 0.0, |m, v| v.min(m));

    let n3x_max = n3x.iter().fold(0.0 / 0.0, |m, v| v.max(m));
    let n3x_min = n3x.iter().fold(0.0 / 0.0, |m, v| v.min(m));
    let n3y_max = n3y.iter().fold(0.0 / 0.0, |m, v| v.max(m));
    let n3y_min = n3y.iter().fold(0.0 / 0.0, |m, v| v.min(m));

    let x_max = n1x_max.max(n2x_max.max(n3x_max)) + graph_margin;
    let x_min = n1x_min.min(n2x_min.min(n3x_min)) - graph_margin;
    let y_max = n1y_max.max(n2y_max.max(n3y_max)) + graph_margin;
    let y_min = n1y_min.min(n2y_min.min(n3y_min)) - graph_margin;

    // draw
    let root = BitMapBackend::new(&file_name, (2560, 1440)).into_drawing_area();
    root.fill(&WHITE).unwrap();

    // setting graph
    let mut chart = ChartBuilder::on(&root)
        .caption(caption, ("sans-serif", 50).into_font())
        .margin(10)
        .x_label_area_size(30)
        .y_label_area_size(30)
        .build_cartesian_2d(
            (x_min as f32)..(x_max as f32),
            (y_min as f32)..(y_max as f32),
        )
        .unwrap();

    chart.configure_mesh().draw().unwrap();

    chart
    .draw_series(PointSeries::of_element(
        (0..n1x.len()).map(|i| (n1x[i] as f32, n1y[i] as f32)),
        1,
        ShapeStyle::from(&RED).filled(),
        &|coord, size, style| EmptyElement::at(coord) + Circle::new((0, 0), size, style),
    ))
    .unwrap();

    chart
    .draw_series(PointSeries::of_element(
        (0..n1x.len()).map(|i| (n2x[i] as f32, n2y[i] as f32)),
        1,
        ShapeStyle::from(&GREEN).filled(),
        &|coord, size, style| EmptyElement::at(coord) + Circle::new((0, 0), size, style),
    ))
    .unwrap();

    chart
    .draw_series(PointSeries::of_element(
        (0..n1x.len()).map(|i| (n3x[i] as f32, n3y[i] as f32)),
        1,
        ShapeStyle::from(&BLUE).filled(),
        &|coord, size, style| EmptyElement::at(coord) + Circle::new((0, 0), size, style),
    ))
    .unwrap();
}

fn main() {
    let delta_t = 0.01;
    let mut draw_intv = 10.0;

    let mut n1x: Vec<f64> = vec![];
    let mut n1y: Vec<f64> = vec![];
    let mut n2x: Vec<f64> = vec![];
    let mut n2y: Vec<f64> = vec![];
    let mut n3x: Vec<f64> = vec![];
    let mut n3y: Vec<f64> = vec![];

    let mut set = embedded_runge_kutta::IntegralSettings::default();
    set.end_time = delta_t;
    set.min_delta_t = 1.0e-10;
    set.tol = 1.0e-6;
    let mut vec: Vec<f64> = vec![-2.0, -1.0, 0.0, 0.0,
                                  1.0, -1.0, 0.0, 0.0,
                                  1.0,  3.0, 0.0, 0.0];
    
    for _i in 0..7100 {
        vec = set.dormand_prince_vec(Box::new(three_body), &vec);
        //println!("{}, {}, {}, {}, {}, {}, {}, {}", set.time, set.delta_t, vec[0], vec[1], vec[4], vec[5], vec[8], vec[9]);
        n1x.push(vec[0]); n1y.push(vec[1]);
        n2x.push(vec[4]); n2y.push(vec[5]);
        n3x.push(vec[8]); n3y.push(vec[9]);

        if set.time > draw_intv {
            draw(set.time, &n1x, &n1y, &n2x, &n2y, &n3x, &n3y);
            n1x.clear(); n1y.clear();
            n2x.clear(); n2y.clear();
            n3x.clear(); n3y.clear();
            draw_intv += 10.0;
        }

        set.end_time += delta_t;
    }
}
