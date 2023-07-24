#[derive(Debug)]
pub struct IntegralSettings {
    pub delta_t: f64,
    pub time: f64,
    pub end_time: f64,
    pub tol: f64,
    pub max_delta_t: f64,
    pub min_delta_t: f64,
}

impl Default for IntegralSettings {
    fn default() -> Self {
        Self {
            delta_t: 1.0e-3,
            time: 0.0,
            end_time: 1.0,
            tol: 1.0e-9,
            max_delta_t: 1.0e-1,
            min_delta_t: 1.0e-12,
        }
    }
}

impl IntegralSettings {
    #[allow(dead_code)]
    pub fn new(dt: f64, t: f64, end_t: f64, set_tol: f64, min_dt: f64, max_dt: f64) -> Self {
        IntegralSettings {
            delta_t: dt,
            time: t,
            end_time: end_t,
            tol: set_tol,
            max_delta_t: min_dt,
            min_delta_t: max_dt,
        }
    }

    #[allow(dead_code)]
    pub fn dormand_prince_vec(
        self: &mut IntegralSettings,
        func: Box<dyn Fn(&Vec<f64>) -> Vec<f64>>,
        vec: &Vec<f64>,
    ) -> Vec<f64> {
        let dim = vec.len();
        let mut ret = vec.clone();
        loop {
            if (self.time + self.delta_t) > self.end_time {
                self.delta_t = self.end_time - self.time;
                // k1
                let mut vec1 = ret.clone();
                for i in 0..dim {
                    vec1[i] = ret[i];
                }
                let mut k1 = vec![0.0; dim];
                for i in 0..dim {
                    k1[i] = func(&vec1)[i];
                };
                // k2
                let mut vec2 = vec![0.0; dim];
                for i in 0..dim {
                    vec2[i] = ret[i] + self.delta_t *     1.0 /    5.0 * k1[i];
                }
                let mut k2 = vec![0.0; dim];
                for i in 0..dim {
                    k2[i] = func(&vec2)[i];
                }
                // k3
                let mut vec3 = vec![0.0; dim];
                for i in 0..dim {
                    vec3[i] = ret[i] + self.delta_t *     3.0 /   40.0 * k1[i] + self.delta_t *     9.0 /   40.0 * k2[i];
                }
                let mut k3 = vec![0.0; dim];
                for i in 0..dim {
                    k3[i] = func(&vec3)[i];
                }
                // k4
                let mut vec4 = vec![0.0; dim];
                for i in 0..dim {
                    vec4[i] = ret[i] + self.delta_t *    44.0 /   45.0 * k1[i] - self.delta_t *    56.0 /   15.0 * k2[i] + self.delta_t *    32.0 /    9.0 * k3[i];
                }
                let mut k4 = vec![0.0; dim];
                for i in 0..dim {
                    k4[i] = func(&vec4)[i];
                }
                // k5
                let mut vec5 = vec![0.0; dim];
                for i in 0..dim {
                    vec5[i] = ret[i] + self.delta_t * 19372.0 / 6561.0 * k1[i] - self.delta_t * 25360.0 / 2187.0 * k2[i] + self.delta_t * 64448.0 / 6561.0 * k3[i] - self.delta_t * 212.0 / 729.0 * k4[i];
                }
                let mut k5 = vec![0.0; dim];
                for i in 0..dim {
                    k5[i] = func(&vec5)[i];
                }
                // k6
                let mut vec6 = vec![0.0; dim];
                for i in 0..dim {
                    vec6[i] = ret[i] + self.delta_t *  9017.0 / 3168.0 * k1[i] - self.delta_t *   355.0 /   33.0 * k2[i] + self.delta_t * 46732.0 / 5247.0 * k3[i] + self.delta_t *  49.0 / 176.0 * k4[i] - self.delta_t * 5103.0 / 18656.0 * k5[i];
                }
                let mut k6 = vec![0.0; dim];
                for i in 0..dim {
                    k6[i] = func(&vec6)[i];
                }
                // k7
                let mut vec7 = vec![0.0; dim];
                for i in 0..dim {
                    vec7[i] = ret[i] + self.delta_t *    35.0 /  384.0 * k1[i]                                        + self.delta_t *   500.0 / 1113.0 * k3[i] + self.delta_t * 125.0 / 192.0 * k4[i] - self.delta_t * 2187.0 /  6784.0 * k5[i] + self.delta_t * 11.0 / 84.0 * k6[i];
                }
                let mut k7 = vec![0.0; dim];
                for i in 0..dim {
                    k7[i] = func(&vec7)[i];
                }
                //
                for i in 0..dim {
                    ret[i] = ret[i] + self.delta_t * (5179.0 / 57600.0 * k1[i] + 7571.0 / 16695.0 * k3[i] + 393.0 / 640.0 * k4[i] - 92097.0 / 339200.0 * k5[i] + 187.0 / 2100.0 * k6[i] + 1.0 / 40.0 * k7[i]);
                }
                self.time += self.delta_t;
                break;
            }
            // k1
            let mut vec1 = ret.clone();
            for i in 0..dim {
                vec1[i] = ret[i];
            }
            let mut k1 = vec![0.0; dim];
            for i in 0..dim {
                k1[i] = func(&vec1)[i];
            };
            // k2
            let mut vec2 = vec![0.0; dim];
            for i in 0..dim {
                vec2[i] = ret[i] + self.delta_t *     1.0 /    5.0 * k1[i];
            }
            let mut k2 = vec![0.0; dim];
            for i in 0..dim {
                k2[i] = func(&vec2)[i];
            }
            // k3
            let mut vec3 = vec![0.0; dim];
            for i in 0..dim {
                vec3[i] = ret[i] + self.delta_t *     3.0 /   40.0 * k1[i] + self.delta_t *     9.0 /   40.0 * k2[i];
            }
            let mut k3 = vec![0.0; dim];
            for i in 0..dim {
                k3[i] = func(&vec3)[i];
            }
            // k4
            let mut vec4 = vec![0.0; dim];
            for i in 0..dim {
                vec4[i] = ret[i] + self.delta_t *    44.0 /   45.0 * k1[i] - self.delta_t *    56.0 /   15.0 * k2[i] + self.delta_t *    32.0 /    9.0 * k3[i];
            }
            let mut k4 = vec![0.0; dim];
            for i in 0..dim {
                k4[i] = func(&vec4)[i];
            }
            // k5
            let mut vec5 = vec![0.0; dim];
            for i in 0..dim {
                vec5[i] = ret[i] + self.delta_t * 19372.0 / 6561.0 * k1[i] - self.delta_t * 25360.0 / 2187.0 * k2[i] + self.delta_t * 64448.0 / 6561.0 * k3[i] - self.delta_t * 212.0 / 729.0 * k4[i];
            }
            let mut k5 = vec![0.0; dim];
            for i in 0..dim {
                k5[i] = func(&vec5)[i];
            }
            // k6
            let mut vec6 = vec![0.0; dim];
            for i in 0..dim {
                vec6[i] = ret[i] + self.delta_t *  9017.0 / 3168.0 * k1[i] - self.delta_t *   355.0 /   33.0 * k2[i] + self.delta_t * 46732.0 / 5247.0 * k3[i] + self.delta_t *  49.0 / 176.0 * k4[i] - self.delta_t * 5103.0 / 18656.0 * k5[i];
            }
            let mut k6 = vec![0.0; dim];
            for i in 0..dim {
                k6[i] = func(&vec6)[i];
            }
            // k7
            let mut vec7 = vec![0.0; dim];
            for i in 0..dim {
                vec7[i] = ret[i] + self.delta_t *    35.0 /  384.0 * k1[i]                                        + self.delta_t *   500.0 / 1113.0 * k3[i] + self.delta_t * 125.0 / 192.0 * k4[i] - self.delta_t * 2187.0 /  6784.0 * k5[i] + self.delta_t * 11.0 / 84.0 * k6[i];
            }
            let mut k7 = vec![0.0; dim];
            for i in 0..dim {
                k7[i] = func(&vec7)[i];
            }
            //
            let mut x5 = vec![0.0; dim];
            let mut r = vec![0.0; dim];
            for i in 0..dim {
                x5[i] = ret[i] + self.delta_t * (5179.0 / 57600.0 * k1[i] + 7571.0 / 16695.0 * k3[i] + 393.0 / 640.0 * k4[i] - 92097.0 / 339200.0 * k5[i] + 187.0 / 2100.0 * k6[i] + 1.0 / 40.0 * k7[i]);
                r[i] = (71.0 / 57600.0 * k1[i] - 71.0 / 16695.0 * k3[i] + 71.0 / 1920.0 * k4[i] - 17253.0 / 339200.0 * k5[i] + 22.0 / 525.0 * k6[i] - 1.0 / 40.0 * k7[i]).abs();
            }
            let r: f64 = r.iter().fold(0.0 / 0.0, |m, v| v.max(m));
            if r > self.tol {
                self.delta_t = 0.99 * self.delta_t;
            } else {
                ret = x5.clone();
                self.time += self.delta_t;
                self.delta_t = 1.001 * self.delta_t;
            }
            if self.delta_t > self.max_delta_t {
                self.delta_t = self.max_delta_t;
            } else if self.delta_t < self.min_delta_t {
                // しょうがないので時間を進める。レヴィ・チヴィタ変換などすべき。もしくは計算スキームの変更、 f128 の使用などが考えられる。
                ret = x5.clone();
                self.time += self.delta_t;
                self.delta_t = self.min_delta_t;
                //println!("{:?}, {:?}, {:?}, {:?}", self.time, self.delta_t, r, ((ret[0] - ret[4]).powf(2.0) + (ret[1] - ret[5]).powf(2.0)).powf(0.5));
            }
        }
        ret
    }

    #[allow(dead_code)]
    pub fn dormand_prince(
        self: &mut IntegralSettings,
        func: Box<dyn Fn(f64) -> f64>,
        mut x: f64,
    ) -> f64 {
        loop {
            if (self.time + self.delta_t) > self.end_time {
                self.delta_t = self.end_time - self.time;
                let k1 = func(x);
                let k2 = func(x + self.delta_t *     1.0 /    5.0 * k1);
                let k3 = func(x + self.delta_t *     3.0 /   40.0 * k1 + self.delta_t *     9.0 /   40.0 * k2);
                let k4 = func(x + self.delta_t *    44.0 /   45.0 * k1 - self.delta_t *    56.0 /   15.0 * k2 + self.delta_t *    32.0 /    9.0 * k3);
                let k5 = func(x + self.delta_t * 19372.0 / 6561.0 * k1 - self.delta_t * 25360.0 / 2187.0 * k2 + self.delta_t * 64448.0 / 6561.0 * k3 - self.delta_t * 212.0 / 729.0 * k4);
                let k6 = func(x + self.delta_t *  9017.0 / 3168.0 * k1 - self.delta_t *   355.0 /   33.0 * k2 + self.delta_t * 46732.0 / 5247.0 * k3 + self.delta_t *  49.0 / 176.0 * k4 - self.delta_t * 5103.0 / 18656.0 * k5);
                let k7 = func(x + self.delta_t *    35.0 /  384.0 * k1                                        + self.delta_t *   500.0 / 1113.0 * k3 + self.delta_t * 125.0 / 192.0 * k4 - self.delta_t * 2187.0 /  6784.0 * k5 + self.delta_t * 11.0 / 84.0 * k6);
                x = x + self.delta_t * (5179.0 / 57600.0 * k1 + 7571.0 / 16695.0 * k3 + 393.0 / 640.0 * k4 - 92097.0 / 339200.0 * k5 + 187.0 / 2100.0 * k6 + 1.0 / 40.0 * k7);
                self.time += self.delta_t;
                break;
            }
            let k1 = func(x);
            let k2 = func(x + self.delta_t *     1.0 /     5.0 * k1);
            let k3 = func(x + self.delta_t *     3.0 /    40.0 * k1 + self.delta_t *     9.0 /   40.0 * k2);
            let k4 = func(x + self.delta_t *    44.0 /    45.0 * k1 - self.delta_t *    56.0 /   15.0 * k2 + self.delta_t *    32.0 /     9.0 * k3);
            let k5 = func(x + self.delta_t * 19372.0 /  6561.0 * k1 - self.delta_t * 25360.0 / 2187.0 * k2 + self.delta_t * 64448.0 /  6561.0 * k3 - self.delta_t * 212.0 / 729.0 * k4);
            let k6 = func(x + self.delta_t *  9017.0 /  3168.0 * k1 - self.delta_t *   355.0 /   33.0 * k2 + self.delta_t * 46732.0 /  5247.0 * k3 + self.delta_t *  49.0 / 176.0 * k4 - self.delta_t *  5103.0 /  18656.0 * k5);
            let k7 = func(x + self.delta_t *    35.0 /   384.0 * k1                                        + self.delta_t *   500.0 /  1113.0 * k3 + self.delta_t * 125.0 / 192.0 * k4 - self.delta_t *  2187.0 /   6784.0 * k5 + self.delta_t *  11.0 /   84.0 * k6);
            //let x4 = x + self.delta_t * (       35.0 /   384.0 * k1                                        +                  500.0 /  1113.0 * k3 +                125.0 / 192.0 * k4 -                 2187.0 /   6784.0 * k5 +                 11.0 /   84.0 * k6);
            let x5 = x + self.delta_t * (     5179.0 / 57600.0 * k1                                        +                 7571.0 / 16695.0 * k3 +                393.0 / 640.0 * k4 -                92097.0 / 339200.0 * k5 +                187.0 / 2100.0 * k6 + 1.0 / 40.0 * k7);
            let r = (71.0 / 57600.0 * k1 - 71.0 / 16695.0 * k3 + 71.0 / 1920.0 * k4 - 17253.0 / 339200.0 * k5 + 22.0 / 525.0 * k6 - 1.0 / 40.0 * k7).abs();
            if r > self.tol {
                self.delta_t = 0.8 * self.delta_t;
            } else {
                x = x5;
                self.time += self.delta_t;
                self.delta_t =  1.001 * self.delta_t; // * (self.tol * self.delta_t / r).powf(1.0 / 5.0);
            }
            if self.delta_t > self.max_delta_t {
                self.delta_t = self.max_delta_t;
            } else if self.delta_t < self.min_delta_t {
                self.delta_t = self.min_delta_t;
            }
        }
        x
    }

    #[allow(dead_code)]
    pub fn classical_runge_kutta(
        self: &mut IntegralSettings,
        func: Box<dyn Fn(f64) -> f64>,
        mut x: f64,
    ) -> f64 {
        let mut flag = 0;
        loop {
            self.time += self.delta_t;
            if self.time > self.end_time {
                self.delta_t = self.time - self.end_time;
                flag = 1;
            }
            let k1 = func(x);
            let k2 = func(x + self.delta_t / 2.0 * k1);
            let k3 = func(x + self.delta_t / 2.0 * k2);
            let k4 = func(x + self.delta_t * k3);
            x += self.delta_t / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
            if flag == 1 {
                break;
            }
        }
        x
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    pub fn id(x: f64) -> f64 {
        x
    }

    #[test]
    fn classical_runge_kutta_1000steps() {
        let mut set = IntegralSettings::default();
        let mut x = 1.0;
        x = set.classical_runge_kutta(Box::new(id), x);
        assert_eq!(x, 2.7155649053185478);
        assert_eq!(set.delta_t, 6.661338147750939e-16);
        assert_eq!(set.end_time, 1.0);
        assert_eq!(set.time, 1.0000000000000007);
    }

    #[test]
    fn dormand_prince_napier() {
        let mut set = IntegralSettings::default();
        set.end_time = 1.0;
        set.tol = 1.0e-12;
        let mut x = 1.0;
        x = set.dormand_prince(Box::new(id), x);
        assert_eq!((x - 2.718281828459045235360287471352) / 2.718281828459045235360287471352, 5.2278812911970694e-15);
    }

    #[test]
    fn dormand_prince_napier_long() {
        let mut set = IntegralSettings::default();
        set.end_time = 10.0;
        set.tol = 1.0e-9;
        let mut x = 1.0;
        x = set.dormand_prince(Box::new(id), x);
        assert_eq!((x - 22026.4657948067165169579) / 22026.4657948067165169579, 4.317881989775347e-12);
    }

    #[allow(dead_code)]
    pub fn harmonic_oscillator(x: &Vec<f64>) -> Vec<f64> {
        let mut ret = vec![0.0; x.len()];
        ret[0] = - x[1];
        ret[1] = x[0];
        ret
    }

    #[test]
    fn harmonic_oscillator_2pi() {
        let mut vec = vec![1.0, 0.0];
        let mut set = IntegralSettings::default();
        set.end_time = 2.0 * std::f64::consts::PI;
        set.tol = 1.0e-12;
        let ret = set.dormand_prince_vec(Box::new(harmonic_oscillator), &mut vec);
        assert_eq!(ret[0], 1.0000000000000127);
        assert_eq!(ret[1], 2.6936948765293733e-12);
    }
}
