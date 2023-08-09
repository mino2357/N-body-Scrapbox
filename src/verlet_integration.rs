use super::kd_tree;

#[allow(dead_code)]
#[derive(Debug, Clone)]
pub struct VerletIntegration {
    pub dt: f64,
    pub epsilon: f64,
    pub radius: f64,
    pub kd_tree: kd_tree::KDTree,
    pub vec1: kd_tree::Points2D,
    pub vec2: kd_tree::Points2D,
    pub vec3: kd_tree::Points2D,
}

impl VerletIntegration {
    #[allow(dead_code)]
    pub fn new() -> Self {
        VerletIntegration {
            dt: 1.0e-4,
            epsilon: 1.0e-3,
            radius: 1.0e1,
            kd_tree: kd_tree::KDTree::new(&kd_tree::Grid2D { x: 0.0, y: 0.0 }, 0),
            vec1: kd_tree::Points2D::new(),
            vec2: kd_tree::Points2D::new(),
            vec3: kd_tree::Points2D::new(),
        }
    }

    #[allow(dead_code)]
    pub fn verlet_integration(&mut self, iter: usize) {
        for i in 0..self.vec1.points.len() {
            self.vec1.points[i].x = 2.0 * self.vec2.points[i].x - self.vec3.points[i].x + self.dt * self.dt * self.gravitation(i, iter).x;
            self.vec1.points[i].y = 2.0 * self.vec2.points[i].y - self.vec3.points[i].y + self.dt * self.dt * self.gravitation(i, iter).y;
        }
        for i in 0..self.vec1.points.len() {
            self.vec3.points[i].x = self.vec2.points[i].x;
            self.vec3.points[i].y = self.vec2.points[i].y;
            self.vec2.points[i].x = self.vec1.points[i].x;
            self.vec2.points[i].y = self.vec1.points[i].y;
        }
    }

    #[allow(dead_code)]
    pub fn gravitation(&mut self, index: usize, iter: usize) -> kd_tree::Grid2D {
        let mut force = kd_tree::Grid2D::new(0.0, 0.0);
        if iter == 0 {
            self.kd_tree = kd_tree::KDTree::construct_kd_tree(&self.vec2);
        }
        let near = self.kd_tree.neighbor_search(&self.vec2.points[index], self.radius);
        let epsilon2 = self.epsilon * self.epsilon;
        for i in near {
            let r_x = self.vec2.points[i].x - self.vec2.points[index].x;
            let r_y = self.vec2.points[i].y - self.vec2.points[index].y;
            let r = (r_x * r_x + r_y * r_y + epsilon2).sqrt();
            if r > self.epsilon {
                force.x += r_x / (r * r * r);
                force.y += r_y / (r * r * r);
            }
        }
        force
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn two_body() {
        let mut body = VerletIntegration::new();
        body.vec1.points.push(kd_tree::Grid2D { x: 0.0, y: 0.0 });
        body.vec1.points.push(kd_tree::Grid2D { x: 0.0, y: 0.0 });
        body.vec2.points.push(kd_tree::Grid2D { x: -1.0, y: 0.0 });
        body.vec2.points.push(kd_tree::Grid2D { x: 1.0, y: 0.0 });
        body.vec3.points.push(kd_tree::Grid2D { x: -1.0, y: 0.1 });
        body.vec3.points.push(kd_tree::Grid2D { x: 1.0, y: -0.1 });
        body.verlet_integration(0);
        body.verlet_integration(0);
        println!("{:?}", body.vec1.points);

        assert_eq!(body.vec1.points[0].x, 0.0);
    }
}