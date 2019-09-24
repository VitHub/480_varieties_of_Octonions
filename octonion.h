
class octonion {
    static int default_mult;
public:
    double guts[8];

    octonion () = delete;
    octonion (octonion const &) = default;
    octonion (octonion &&) = default;
    octonion & operator= (octonion const &) = default;
    octonion & operator= (octonion &&) = default;
    ~octonion () = default;

    octonion (
        double const e0, double const e1,
        double const e2, double const e3,
        double const e4, double const e5,
        double const e6, double const e7
    ) {
        guts[0] = e0; guts[1] = e1;
        guts[2] = e2; guts[3] = e3;
        guts[4] = e4; guts[5] = e5;
        guts[6] = e6; guts[7] = e7;
    }

    octonion (double const (& g)[8]) {
        for (int i {0}; i < 8; ++i) guts[i] = g[i];
    }

    octonion operator+ () const {
        return octonion {
            +guts[0], +guts[1], +guts[2], +guts[3],
            +guts[4], +guts[5], +guts[6], +guts[7]
        };
    }
    octonion operator~ () const {
        return octonion {
            +guts[0], -guts[1], -guts[2], -guts[3],
            -guts[4], -guts[5], -guts[6], -guts[7]
        };
    }
    octonion operator- () const {
        return octonion {
            -guts[0], -guts[1], -guts[2], -guts[3],
            -guts[4], -guts[5], -guts[6], -guts[7]
        };
    }

    octonion operator+ (octonion const & o) const {
        return octonion {
            guts[0] + o.guts[0], guts[1] + o.guts[1],
            guts[2] + o.guts[2], guts[3] + o.guts[3],
            guts[4] + o.guts[4], guts[5] + o.guts[5],
            guts[6] + o.guts[6], guts[7] + o.guts[7]
        };
    }
    octonion operator- (octonion const & o) const {
        return octonion {
            guts[0] - o.guts[0], guts[1] - o.guts[1],
            guts[2] - o.guts[2], guts[3] - o.guts[3],
            guts[4] - o.guts[4], guts[5] - o.guts[5],
            guts[6] - o.guts[6], guts[7] - o.guts[7]
        };
    }

    static void set_default_mult (int const choose_mult) {
        if (choose_mult <   0)
            throw fail {"octonion::set_default_mult ... choose_mult <   0"};
        if (choose_mult > 479)
            throw fail {"octonion::set_default_mult ... choose_mult > 479"};
        default_mult = choose_mult;
    }

    static int get_default_mult () { return default_mult; }

    octonion mult (octonion const & second, int const choose_mult) const {
        if (choose_mult < 0)
            throw fail {"octonion::mult ... choose_mult < 0"};
        if (choose_mult > 479)
            throw fail {"octonion::mult ... choose_mult > 479"};
        int const (& source)[8][8] {raw_mult[choose_mult]};
        octonion const & first {*this};

        double r[8];
        for (int i {0}; i < 8; ++i) r[i] = 0;

        for (int i {0}; i < 8; ++i) {
            for (int j {0}; j < 8; ++j) {
                int const ij {source[i][j]};
                if (ij == +8)
                    r[0] += first.guts[0] * second.guts[0];
                else if (ij == -8)
                    r[0] -= first.guts[i] * second.guts[j];
                else if (ij > 0)
                    r[+ij] += first.guts[i] * second.guts[j];
                else if (ij < 0)
                    r[-ij] -= first.guts[i] * second.guts[j];
                else
                   throw fail {"octonion::mult ... ij == 0"};
            }
        }

        return octonion {r};
    }

    octonion operator* (octonion const & second) const {
        return mult (second, default_mult);
    }

    octonion mult_aba (octonion const & second) const {
        // Calculates (*this) * second * (*this).
        // The value of default_mult does not matter.

        double const (& t)[8] {this->guts};
        double const (& s)[8] {second.guts};
        double r[8];
        double const t0 {t[0]};
        double const s0 {s[0]};

        r[0] = t0 * s0 * t0;
        for (int i {1}; i < 8; ++i) {
            double const ti {t[i]};
            double const si {s[i]};
            r[i] = -ti * si * ti;
            r[0] -= t0 * si * ti;
            r[0] -= ti * s0 * ti;
            r[0] -= ti * si * t0;
            r[i] += ti * s0 * t0;
            r[i] += t0 * si * t0;
            r[i] += t0 * s0 * ti;
            for (int j {1}; j < 8; ++j) {
                if (i == j) continue;
                double const tj {t[j]};
                double const sj {s[j]};
                r[i] -= ti * sj * tj;
                r[i] += tj * si * tj;
                r[i] -= tj * sj * ti;
            }
        }
        return octonion {r};
    }

    octonion mult_conj_aab (octonion const & second) const {
        // calculates (~ *this) * (*this) * second
        // the value of default_mult does not matter

        double const (& t)[8] {this->guts};
        double const (& s)[8] {second.guts};
        double r[8];
        double const t0 {t[0]};
        double const s0 {s[0]};

        r[0] = t0 * t0 * s0;
        for (int i {1}; i < 8; ++i) {
            double const ti {t[i]};
            double const si {s[i]};
            r[i] = +ti * ti * si;
            r[0] -= t0 * ti * si;
            r[0] += ti * t0 * si;
            r[0] += ti * ti * s0;
            r[i] -= ti * t0 * s0;
            r[i] += t0 * ti * s0;
            r[i] += t0 * t0 * si;
            for (int j {1}; j < 8; ++j) {
                if (i == j) continue;
                double const tj {t[j]};
                double const sj {s[j]};
                r[i] += ti * tj * sj;
                r[i] -= tj * ti * sj;
                r[i] += tj * tj * si;
            }
        }
        return octonion {r};
    }

    octonion operator* (double const o) const {
        return octonion {
            guts[0] * o, guts[1] * o, guts[2] * o, guts[3] * o,
            guts[4] * o, guts[5] * o, guts[6] * o, guts[7] * o,
        };
    }
    octonion operator/ (double const o) const {
        return octonion {
            guts[0] / o, guts[1] / o, guts[2] / o, guts[3] / o,
            guts[4] / o, guts[5] / o, guts[6] / o, guts[7] / o,
        };
    }

    double squ_abs () const {
        double total {0.0};
        for (int i {0}; i < 8; ++i)
            total += guts[i] * guts[i];
        return total;
    }
    double abs () const { return sqrt (squ_abs()); }

    bool operator< (octonion const & o) const {
        for (int i {0}; i < 8; ++i) {
            if (guts[i] < o.guts[i]) return true;
            if (guts[i] > o.guts[i]) return false;
        }
        return false;
    }

    octonion recip () const
        { return operator~() / squ_abs(); }

    void view (ostream & o) const {
        o << "[";
        for (auto const i : guts) {
            if (i > 0) {
                o << std::showpos;
                o << setw (12) << i << " ";
                o << std::noshowpos;
            } else {
                o << setw (12) << i << " ";
            }
        }
        o << "]";
    }
};

int octonion::default_mult {42};

ostream & operator<< (ostream & ost, octonion const oct)
    { oct.view (ost); return ost; }

