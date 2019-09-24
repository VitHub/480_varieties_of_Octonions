
void demo1 (int const mult) {
    octonion::set_default_mult (mult);

    cout << "\n\n ========================== ";
    cout << "\n\n demo1 using multiplication table " << octonion::get_default_mult();
    cout << "\n verify some algebraic laws";

    cout << "\n ";
    cout << "\n a.abs * b.abs = " << a_abs * b_abs;
    cout << "\n (a * b).abs   = " << (a * b).abs ();

    {
        cout << "\n\n The following pairs will be equal (alternate associativity): ";
        {
            octonion const o1 {(a *  a) * b };
            octonion const o2 { a * (a  * b)};
            cout << "\n ";
            cout << "\n (a *  a) * b  = " << o1;
            cout << "\n  a * (a  * b) = " << o2;
        } {
            octonion const o1 {(a *  b) * a };
            octonion const o2 { a * (b  * a)};
            cout << "\n ";
            cout << "\n (a *  b) * a  = " << o1;
            cout << "\n  a * (b  * a) = " << o2 ;
        } {
            octonion const o1 {(b *  a) * a };
            octonion const o2 { b * (a  * a)};
            cout << "\n ";
            cout << "\n (b *  a) * a  = " << o1;
            cout << "\n  b * (a  * a) = " << o2;
        }
    } {
        cout << "\n\n The following pair or quadruple will be equal (conjugate alternate associativity): ";
        {
            octonion const o1 {(a *  b) * ~a };
            octonion const o2 { a * (b  * ~a)};
            cout << "\n ";
            cout << "\n ( a *  b) * ~a  = " << o1;
            cout << "\n   a * (b  * ~a) = " << o2 ;
        } {
            octonion const o1 {(~a *  a) *  b };
            octonion const o2 { ~a * (a  *  b)};
            octonion const o3 {( b *  a) * ~a };
            octonion const o4 {  b * (a  * ~a)};
            cout << "\n ";
            cout << "\n (~a *  a) *  b  = " << o1;
            cout << "\n  ~a * (a  *  b) = " << o2;
            cout << "\n ( b *  a) * ~a  = " << o3;
            cout << "\n   b * (a  * ~a) = " << o4;
        }
    } {
        cout << "\n\n The following pairs will be equal (distributivity): ";
        {
            octonion const o1 {(a + b) * c};
            octonion const o2 {a * c + b * c};
            cout << "\n ";
            cout << "\n (a + b) * c   = " << o1;
            cout << "\n a * c + b * c = " << o2;
        } {
            octonion const o1 {a * (b + c)};
            octonion const o2 {a * b + a * c};
            cout << "\n ";
            cout << "\n a * (b + c)   = " << o1;
            cout << "\n a * b + a * c = " << o2;
        } {
            octonion const o1 {(a - b) * c};
            octonion const o2 {a * c - b * c};
            cout << "\n ";
            cout << "\n (a - b) * c   = " << o1;
            cout << "\n a * c - b * c = " << o2;
        } {
            octonion const o1 {a * (b - c)};
            octonion const o2 {a * b - a * c};
            cout << "\n ";
            cout << "\n a * (b - c)   = " << o1;
            cout << "\n a * b - a * c = " << o2;
        }
    } {
        cout << "\n\n The following pairs or triplet will be equal (Moufang identity): ";
        {
            octonion const o1 {  a * (b  * (a  * c))};
            octonion const o2 {((a *  b) *  a) * c  };
            cout << "\n ";
            cout << "\n   a * (b  * (a  * c)) = " << o1;
            cout << "\n ((a *  b) *  a) * c   = " << o2;
        } {
            octonion const o1 {  b * (a  * (c  * a))};
            octonion const o2 {((b *  a) *  c) * a  };
            cout << "\n ";
            cout << "\n   b * (a  * (c  * a)) = " << o1;
            cout << "\n ((b *  a) *  c) * a   = " << o2;
        } {
            octonion const o1 {(a *  (b  *  c)) * a };
            octonion const o2 {(a *   b) * (c   * a)};
            octonion const o3 { a * ((b  *  c)  * a)};
            cout << "\n ";
            cout << "\n (a *  (b  *  c)) * a  = " << o1;
            cout << "\n (a *   b) * (c   * a) = " << o2;
            cout << "\n  a * ((b  *  c)  * a) = " << o3;
        }
    } {
        cout << "\n\n The following pair will be equal (conjugate Moufang identity): ";
        {
            octonion const o1 {(~a *  (b * c)) * a };
            octonion const o2 { ~a * ((b * c)  * a)};
            cout << "\n ";
            cout << "\n (~a *  (b  *  c)) * a  = " << o1;
            cout << "\n  ~a * ((b  *  c)  * a) = " << o2;
        }
    } {
        cout << "\n\n The following pair will in general not be equal (noncommutativity): ";
        octonion const o1 {a * b};
        octonion const o2 {b * a};
        cout << "\n ";
        cout << "\n ab = " << o1 << " abs = " << o1.abs();
        cout << "\n ba = " << o2 << " abs = " << o2.abs();
    } {
        cout << "\n\n The following pair will in general not be equal (nonassociativity): ";
        octonion const o1 {(a *  b) * c };
        octonion const o2 { a * (b *  c)};
        cout << "\n ";
        cout << "\n (a *  b) * c  = " << o1 << " abs = " << o1.abs();
        cout << "\n  a * (b  * c) = " << o2 << " abs = " << o2.abs();
    }
}

void demo2 () {
    cout << "\n\n ========================== ";
    cout << "\n\n demo 2: ";
    cout << "\n verify that all 480 products are different";

    struct duet {
        int n;
        octonion o;

        duet (int const j, octonion const & p)
            : n {j}, o {p}
        { }

        bool operator< (duet const & d) const
            { return o < d.o; }
    };

    std::vector<duet> table;

    for (int i {0}; i < 480; ++i) {
        octonion const q {a.mult (b, i)};
        table.emplace_back (i, q);
    }

    std::sort (table.begin(), table.end());

    for (auto const & i : table)
        cout << "\n " << setw (3) << i.n << ": " << i.o;
}

void demo3 () {
    cout << "\n\n ========================== ";
    cout << "\n\n demo 3: ";
    cout << "\n verify invariance";

    cout << "\n  a *  b  * a  = " << a.mult_aba (b);

    for (int i {0}; i < 480; ++i) {
        cout << "\n\n mult table = " << setw(3) << i;

        octonion const ab {a.mult (b, i)};
        octonion const ab_a {ab.mult (a, i)};
        cout << "\n (a *  b) * a  = " << ab_a;

        octonion const ba {b.mult (a, i)};
        octonion const a_ba {a.mult (ba, i)};
        cout << "\n  a * (b  * a) = " << a_ba;
    }
}

void demo4 () {
    cout << "\n\n ========================== ";
    cout << "\n\n demo 4: ";
    cout << "\n verify conjugate invariance";
    cout << "\n  ~a *  a  *  b  = " << a.mult_conj_aab (b);

    for (int i {0}; i < 480; ++i) {
        cout << "\n\n mult table = " << setw(3) << i;

        octonion const c {~a};

        octonion const ca {c.mult (a, i)};
        octonion const ca_b {ca.mult (b, i)};
        cout << "\n (~a *  a) *  b  = " << ca_b;

        octonion const ab {a.mult (b, i)};
        octonion const c_ab {c.mult (ab, i)};
        cout << "\n  ~a * (a  *  b) = " << c_ab;

        octonion const ba {b.mult (a, i)};
        octonion const ba_c {ba.mult (c, i)};
        cout << "\n ( b *  a) * ~a  = " << ba_c;

        octonion const ac {a.mult (c, i)};
        octonion const b_ac {b.mult (ac, i)};
        cout << "\n   b * (a  * ~a) = " << b_ac;
    }
}

void demo5 () {
    cout << "\n\n ========================== ";
    cout << "\n\n demo 5: ";
    cout << "\n\n examine distributivity for a * b * a and ~a * a * b";

    cout << "\n\n The following pairs will be equal (distributivity): ";
    {
        octonion const o1 {a.mult_aba (b) + a.mult_aba (c)};
        octonion const o2 {a.mult_aba (b + c)};
        cout << "\n ";
        cout << "\n a * b * a + a * c * a = " << o1;
        cout << "\n a * (b + c) * a       = " << o2;
    }
    {
        octonion const o1 {a.mult_conj_aab (b) + a.mult_conj_aab (c)};
        octonion const o2 {a.mult_conj_aab (b + c)};
        cout << "\n ";
        cout << "\n ~a * a * b + ~a * a * c = " << o1;
        cout << "\n ~a * a (b + c)          = " << o2;
    }

    cout << "\n\n The following pairs will in general not be equal (nondistributivity): ";
    {
        octonion const o1 {a.mult_aba (c) + b.mult_aba (c)};
        octonion const o2 {(a + b).mult_aba (c)};
        cout << "\n ";
        cout << "\n a * c * a + b * c * b = " << o1;
        cout << "\n (a + b) * c * (a + b) = " << o2;
    } {
        octonion const o1 {a.mult_conj_aab (c) + b.mult_conj_aab (c)};
        octonion const o2 {(a + b).mult_conj_aab (c)};
        cout << "\n ";
        cout << "\n ~a * a * c + ~b * b * c = " << o1;
        cout << "\n ~(a + b) * (a + b) * c  = " << o2;
    }
}


