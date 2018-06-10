#ifndef CRT_EEA_HPP_
#define CRT_EEA_HPP_


/*
 * Function prototypes :
 *
 * const vector<euclidean_ring> gcd_EEA(const euclidean_ring& a, const euclidean_ring& b);
 * const euclidean_ring CRT(const vector<euclidean_ring>& m, const vector<euclidean_ring>& v);
 */


template <typename euclidean_ring>
const vector<euclidean_ring>
gcd_EEA_helper(const euclidean_ring& a, const euclidean_ring& s_a, const euclidean_ring& t_a,
               const euclidean_ring& b, const euclidean_ring& s_b, const euclidean_ring& t_b)
{
    euclidean_ring r, s, t, q, z, u, rho;
    vector<euclidean_ring> res;

    z = 0;
    u = 1;
    r = a%b;
    
    if (r == z) {
        res.push_back(b);
        res.push_back(s_b);
        res.push_back(t_b);
        return res;
    }
    
    else {
        int r_deg = r.leading_index(); // This works only if euclidean_ring is a polynomial ring.
        rho = r.coeff[r_deg];          // If euclidean_ring is such as int or mpq_class,
                                       // then r_deg should be removed and rho should be 1.                              
        r /= rho;
        q = a/b;
        s = (s_a - (q * s_b)) / rho;
        t = (t_a - (q * t_b)) / rho;
        return gcd_EEA_helper(b, s_b, t_b, r, s, t);
    }
}


template <typename euclidean_ring>
const vector<euclidean_ring>
gcd_EEA(const euclidean_ring& a, const euclidean_ring& b)
{
    euclidean_ring u, tmp;
    euclidean_ring s_a, t_a, s_b, t_b;

    tmp = a.coeff[a.leading_index()];
    s_a = u / tmp;
    t_a = 0;
    tmp = b.coeff[b.leading_index()];
    s_b = 0;
    t_b = u / tmp;

    return gcd_EEA_helper(a, s_a, t_a, b, s_b, t_b);
}


template <typename euclidean_ring>
const euclidean_ring
CRT(const vector<euclidean_ring>& m, const vector<euclidean_ring>& v)
{
    euclidean_ring M = m[0];
    for (int i = 1; i < m.size(); i++) {
        M *= m[i];
    }

    vector<euclidean_ring> m_quo;
    for (int i = 0; i < m.size(); i++) {
        m_quo.push_back(M / (m[i]));
    }

    vector<euclidean_ring> C;
    for (int i = 0 ; i < m.size(); i++) {
        vector<euclidean_ring> tmp;
        euclidean_ring a, b, c, d;
        a = 1; b = 0; c = 0; d = 1;
        tmp = gcd_EEA_helper(m_quo[i], a, b, m[i], c, d);
        C.push_back((v[i]*tmp[1]) % m[i]);
    }

    euclidean_ring res;
    res = 0;
    for (int i = 0; i < m.size(); i++) {
        res += (C[i] * m_quo[i]);
    }

    return res;
}


#endif /* CRT_EEA_HPP_ */