#include "Image.h"
#include <cstdlib>

void Image::lighten() {
    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            if (cur.l + 0.1 < 1) {
                cur.l += 0.1;
            } else {
                cur.l = 1;
            }
        }
    }
}
void Image::lighten(double amount) {
    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            if (cur.l + amount < 1) {
                cur.l += amount;
            } else {
                cur.l = 1;
            }
        }
    }
}
void Image::darken() {
    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            if (cur.l - 0.1 > 0) {
                cur.l -= 0.1;
            } else {
                cur.l = 0;
            }
        }
    }
}
void Image::darken(double amount) {
    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            if (cur.l - amount > 0) {
                cur.l -= amount;
            } else {
                cur.l = 0;
            }
        }
    }
}
void Image::saturate() {
    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            if (cur.s + 0.1 < 1) {
                cur.s += 0.1;
            } else {
                cur.s = 1;
            }
        }
    }
}
void Image::saturate(double amount) {
    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            if (cur.s + amount < 1) {
                cur.s += amount;
            } else {
                cur.s = 1;
            }
        }
    }
}
void Image::desaturate() {
    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            if (cur.s - 0.1 > 0) {
                cur.s -= 0.1;
            } else {
                cur.s = 0;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            if (cur.s - amount > 0) {
                cur.s -= amount;
            } else {
                cur.s = 0;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur.s = 0;
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur.h = (int)(cur.h + degrees)%360;
            if (cur.h < 0) {
                cur.h += 360;
            }
        }
    }
}
void Image::illinify() {
    // illini orange = 11
    // illini blue = 216
    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            if (std::abs(cur.h - 11) > std::abs(cur.h - 216)) {
                cur.h = 11;
            } else {
                cur.h = 216;
            }
        }
    }
}
void Image::scale(double factor) {
    PNG* scaled = new PNG(*this);
    resize(width()*factor, height()*factor);

    for (unsigned int i = 0; i < width(); ++i) {
        for (unsigned int j = 0; j < height(); ++j) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur = scaled->getPixel(i/factor, j/factor);
        }
    }
    delete scaled;
}
void Image::scale(unsigned w, unsigned h) {
    if ((double)w/width() < (double)h/height()) {
        scale((double)w/width());
    } else {
        scale((double)h/height());
    }
}