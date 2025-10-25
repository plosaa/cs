// https://www.smqyoj.com/p/DSA0607
// https://www.smqyoj.com/record/68fb2a0b7fc8598513db3977

// compile locally by: `g++ DSA0607.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
/*
example input:
10
1 106465
4 1
1 317721
1 460929
1 644985
1 84185
1 89851
6 81968
1 492737
5 493598
*/

#include "avl.h"

AVLNode *target_child(AVLNode * u) {
    int lc_h = u->lc ? u->lc->height : 0;
    int rc_h = u->rc ? u->rc->height : 0;
    if (lc_h == rc_h) {
        if (islc(u)) return u->lc;
        else return u->rc;
    }
    else {
        return lc_h > rc_h ? u->lc : u->rc;
    }
}

AVLNode *tuning(AVLNode *g, AVLNode *p, AVLNode *v) {
    if (islc(p)) {
        if (islc(v)) return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        else return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
    }
    else {
        if (islc(v)) return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        else return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
    }
}
