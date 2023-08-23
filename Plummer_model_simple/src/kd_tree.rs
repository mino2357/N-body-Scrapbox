#[derive(Debug, Clone, PartialEq, PartialOrd)]
pub struct Grid2D {
    pub x: f64,
    pub y: f64,
}

#[derive(Debug, Clone)]
pub struct Points2D {
    pub points: Vec<Grid2D>,
}

#[allow(dead_code)]
#[derive(Debug, Clone)]
pub struct KDTree {
    id: usize,
    position: Grid2D,
    left: Option<Box<KDTree>>,
    right: Option<Box<KDTree>>,
}

impl Grid2D {
    #[allow(dead_code)]
    pub fn new(x_: f64, y_: f64) -> Self {
        Grid2D { x: x_, y: y_ }
    }

    #[allow(dead_code)]
    pub fn distance_square(&self, point: &Grid2D) -> f64 {
        let dx2 = (self.x - point.x) * (self.x - point.x);
        let dy2 = (self.y - point.y) * (self.y - point.y);
        dx2 + dy2
    }
}

impl Points2D {
    #[allow(dead_code)]
    pub fn new() -> Self {
        Points2D { points: vec![] }
    }

    #[allow(dead_code)]
    pub fn push(&mut self, x_r: f64, y_r: f64) {
        self.points.push(Grid2D { x: x_r, y: y_r });
    }
}

impl KDTree {
    #[allow(dead_code)]
    pub fn new(vector: &Grid2D, id_: usize) -> Self {
        Self {
            id: id_,
            position: vector.clone(),
            left: None,
            right: None,
        }
    }

    #[allow(dead_code)]
    fn number_of_leaves(&self) -> usize {
        match (&self.left, &self.right) {
            (None, None) => 1,
            (Some(left_node), None) => left_node.number_of_leaves(),
            (None, Some(right_node)) => right_node.number_of_leaves(),
            (Some(left_node), Some(right_node)) => {
                left_node.number_of_leaves() + right_node.number_of_leaves()
            }
        }
    }

    #[allow(dead_code)]
    fn is_leaf(&self) -> bool {
        match (&self.left, &self.right) {
            (None, None) => true,
            (Some(_), None) => false,
            (None, Some(_)) => false,
            (Some(_), Some(_)) => false,
        }
    }

    #[allow(dead_code)]
    pub fn neighbor_search(&self, x: &Grid2D, radius: f64) -> Vec<usize> {
        let mut near = vec![0; 0];
        self.search_points_id(x, radius, &mut near, 0);
        near.clone()
    }

    #[allow(dead_code)]
    fn search_points_id(&self, x: &Grid2D, radius: f64, near: &mut Vec<usize>, mut depth: i32) {
        let axis = depth % 2;
        let r_self = self.position.distance_square(x).sqrt();
        if r_self < radius {
            near.push(self.id);
        }

        match axis {
            0 => {
                if self.position.x < x.x - radius {
                    match &self.right {
                        Some(right_node) => {
                            depth += 1;
                            right_node.search_points_id(x, radius, near, depth);
                        }
                        None => {}
                    }
                } else if x.x + radius < self.position.x {
                    match &self.left {
                        Some(left_node) => {
                            depth += 1;
                            left_node.search_points_id(x, radius, near, depth);
                        }
                        None => {}
                    }
                } else {
                    match (&self.right, &self.left) {
                        (Some(left_node), Some(right_node)) => {
                            depth += 1;
                            left_node.search_points_id(x, radius, near, depth);
                            right_node.search_points_id(x, radius, near, depth);
                        }
                        (Some(left_node), None) => {
                            depth += 1;
                            left_node.search_points_id(x, radius, near, depth);
                        }
                        (None, Some(right_node)) => {
                            depth += 1;
                            right_node.search_points_id(x, radius, near, depth);
                        }
                        (None, None) => {}
                    }
                }
            }
            _ => {
                if self.position.y < x.y - radius {
                    match &self.right {
                        Some(right_node) => {
                            depth += 1;
                            right_node.search_points_id(x, radius, near, depth);
                        }
                        None => {}
                    }
                } else if x.y + radius < self.position.y {
                    match &self.left {
                        Some(left_node) => {
                            depth += 1;
                            left_node.search_points_id(x, radius, near, depth);
                        }
                        None => {}
                    }
                } else {
                    match (&self.right, &self.left) {
                        (Some(left_node), Some(right_node)) => {
                            depth += 1;
                            left_node.search_points_id(x, radius, near, depth);
                            right_node.search_points_id(x, radius, near, depth);
                        }
                        (Some(left_node), None) => {
                            depth += 1;
                            left_node.search_points_id(x, radius, near, depth);
                        }
                        (None, Some(right_node)) => {
                            depth += 1;
                            right_node.search_points_id(x, radius, near, depth);
                        }
                        (None, None) => {}
                    }
                }
            }
        }
    }

    #[allow(dead_code)]
    fn insert(&mut self, point: &Grid2D, mut depth: i32, id: usize) {
        let axis = depth % 2;

        match axis {
            0 => {
                if self.position.x > point.x {
                    match &mut self.left {
                        Some(left_node) => {
                            depth += 1;
                            left_node.insert(point, depth, id);
                        }
                        None => {
                            let node = Self::new(point, id);
                            self.left = Some(Box::new(node));
                        }
                    }
                } else {
                    match &mut self.right {
                        Some(right_node) => {
                            depth += 1;
                            right_node.insert(point, depth, id);
                        }
                        None => {
                            let node = Self::new(point, id);
                            self.right = Some(Box::new(node));
                        }
                    }
                }
            }
            _ => {
                if self.position.y > point.y {
                    match &mut self.left {
                        Some(left_node) => {
                            depth += 1;
                            left_node.insert(point, depth, id);
                        }
                        None => {
                            let node = Self::new(point, id);
                            self.left = Some(Box::new(node));
                        }
                    }
                } else {
                    match &mut self.right {
                        Some(right_node) => {
                            depth += 1;
                            right_node.insert(point, depth, id);
                        }
                        None => {
                            let node = Self::new(point, id);
                            self.right = Some(Box::new(node));
                        }
                    }
                }
            }
        }
    }

    #[allow(dead_code)]
    fn create_kd_tree(&mut self, vec: &Points2D) -> Self {
        let depth = 0;
        for i in 1..vec.points.len() {
            self.insert(&vec.points[i], depth, i);
        }
        self.clone()
    }

    #[allow(dead_code)]
    pub fn depth(&self) -> i32 {
        match (&self.left, &self.right) {
            (Some(left), Some(right)) => 1 + (left.depth()).max(right.depth()),
            (None, None) => 0,
            (None, Some(right)) => 1 + right.depth(),
            (Some(left), None) => 1 + left.depth(),
        }
    }

    #[allow(dead_code)]
    pub fn construct_kd_tree(vec: &Points2D) -> KDTree {
        let mut tree = KDTree::new(&Grid2D::new(vec.points[0].x, vec.points[0].y), 0);
        tree.create_kd_tree(vec)
    }

    #[allow(dead_code)]
    pub fn size(&self) -> i32 {
        match (&self.left, &self.right) {
            (Some(left), Some(right)) => 1 + left.size() + right.size(),
            (None, None) => 1,
            (None, Some(right)) => 1 + right.size(),
            (Some(left), None) => 1 + left.size(),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn depth_and_size() {
        use rand::prelude::*;
        let seed: [u8; 32] = [1; 32];
        let mut rng: rand::rngs::StdRng = rand::SeedableRng::from_seed(seed);
        let num_point: usize = 600;

        let mut vec = Points2D::new();

        for _ in 0..num_point {
            let x_r = 2.0 * (rng.gen::<f64>() - 0.5);
            let y_r = 2.0 * (rng.gen::<f64>() - 0.5);
            vec.push(x_r, y_r);
        }

        let tree = KDTree::construct_kd_tree(&mut vec);

        assert_eq!(tree.depth(), 20);
        assert_eq!(tree.size(), 600);
    }

    #[test]
    fn search_1() {
        use rand::prelude::*;
        let seed: [u8; 32] = [1; 32];
        let mut rng: rand::rngs::StdRng = rand::SeedableRng::from_seed(seed);
        let num_point: usize = 10;

        let mut vec = Points2D::new();

        for _ in 0..num_point {
            let x_r = 2.0 * (rng.gen::<f64>() - 0.5);
            let y_r = 2.0 * (rng.gen::<f64>() - 0.5);
            vec.push(x_r, y_r);
        }

        let tree = KDTree::construct_kd_tree(&mut vec);
        let center = Grid2D { x: 0.0, y: 0.0 };
        let radius = 0.4;
        let near = tree.neighbor_search(&center, radius);

        assert_eq!(near, [1 as usize, 9 as usize].to_vec());
    }

    #[test]
    fn search_2() {
        use rand::prelude::*;
        let seed: [u8; 32] = [1; 32];
        let mut rng: rand::rngs::StdRng = rand::SeedableRng::from_seed(seed);
        let num_point: usize = 10;

        let mut vec = Points2D::new();

        for _ in 0..num_point {
            let x_r = 2.0 * (rng.gen::<f64>() - 0.5);
            let y_r = 2.0 * (rng.gen::<f64>() - 0.5);
            vec.push(x_r, y_r);
        }

        let tree = KDTree::construct_kd_tree(&mut vec);
        let center = Grid2D { x: 0.4, y: 0.3 };
        let radius = 0.5;
        let near = tree.neighbor_search(&center, radius);

        assert_eq!(
            near,
            [1 as usize, 2 as usize, 6 as usize, 9 as usize, 5 as usize].to_vec()
        );
    }

    #[test]
    fn count_leaves() {
        use rand::prelude::*;
        let seed: [u8; 32] = [1; 32];
        let mut rng: rand::rngs::StdRng = rand::SeedableRng::from_seed(seed);
        let num_point: usize = 10;

        let mut vec = Points2D::new();

        for _ in 0..num_point {
            let x_r = 2.0 * (rng.gen::<f64>() - 0.5);
            let y_r = 2.0 * (rng.gen::<f64>() - 0.5);
            vec.push(x_r, y_r);
        }

        let tree = KDTree::construct_kd_tree(&mut vec);

        let center = Grid2D { x: 0.4, y: 0.3 };
        let radius = 0.5;
        let mut near = vec![0 as usize; 0];
        tree.search_points_id(&center, radius, &mut near, 0);

        assert_eq!(tree.number_of_leaves(), 4);
    }

    #[test]
    fn random_size_test() {
        use rand::Rng;

        let mut rnd = rand::thread_rng();
        for _ in 0..10 {
            let num_point: i32 = rnd.gen_range(0..100000);
            let mut vec = Points2D::new();
            for _ in 0..num_point {
                let x_r = rnd.gen::<i32>() as f64;
                let y_r = rnd.gen::<i32>() as f64;
                vec.push(x_r, y_r);
            }
            let tree = KDTree::construct_kd_tree(&mut vec);

            assert_eq!(tree.size(), num_point);
        }
    }

    #[allow(dead_code)]
    fn benchmark_pre(size: i32) -> Points2D {
        use rand::Rng;

        let mut rnd = rand::thread_rng();
        let max = size;
        let num_point: i32 = rnd.gen_range(0..max);
        let mut vec = Points2D::new();
        for _ in 0..num_point {
            let x_r = rnd.gen::<i32>() as f64 / max as f64;
            let y_r = rnd.gen::<i32>() as f64 / max as f64;
            vec.push(x_r, y_r);
        }
        vec.clone()
    }

    #[allow(dead_code)]
    fn benchmark(vec: &Points2D) {
        let tree = KDTree::construct_kd_tree(vec);
        let center = Grid2D::new(0.0, 0.0);
        tree.neighbor_search(&center, 0.01);
    }

    #[test]
    #[should_panic]
    fn speed_test() {
        use std::time::Instant;

        let mut test_size = 100;
        loop {
            let vec = benchmark_pre(test_size);

            let start = Instant::now();
            benchmark(&vec);
            let end = start.elapsed();

            println!(
                "{}, {}.{:03}",
                test_size,
                end.as_secs(),
                end.subsec_nanos() / 1_000_000
            );

            test_size = 2 * test_size;

            if test_size > 1_000_000 {
                break;
            }
        }
        assert_eq!(0, 1);
    }
}
