#include "StickerSheet.h"

StickerSheet::StickerSheet (const Image &picture, unsigned max) {
    picture_ = picture;
    max_ = max;
}
StickerSheet::~StickerSheet () {
    for (auto temp: sheet_) {
        delete temp;
        temp = NULL;
    }
}
StickerSheet::StickerSheet (const StickerSheet &other) {
    picture_ = other.picture_;
    max_ = other.max_;
    for (auto temp: other.sheet_) {
        Image* to_add = new Image(*temp);
        sheet_.push_back(to_add);
    }
}
const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    if (this == &other) {
        return *this;
    }
    picture_ = other.picture_;
    max_ = other.max_;
    for (auto temp: sheet_) {
        delete temp;
        temp = NULL;
    }
    for (auto temp: other.sheet_) {
        Image* to_add = new Image(*temp);
        sheet_.push_back(to_add);
    }
    return *this; 
}
void StickerSheet::changeMaxStickers (unsigned max) {
    if (sheet_.size() > max) {
        std::vector<Image*> max_sheet;
        for (unsigned int i = 0; i < max; ++i) {
            max_sheet.push_back(sheet_[i]);
        }
        for (unsigned int j = max; j < sheet_.size(); ++j) {
            removeSticker(j);
        }
        sheet_ = max_sheet;
    }
    max_ = max;
}
int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
    if (max_ == sheet_.size()) {
        return -1;
    }
    Image* to_add = new Image(sticker);
    to_add->x_ = x;
    to_add->y_ = y;
    sheet_.push_back(to_add);
    return sheet_.size() - 1;
}
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
    if (index >= sheet_.size()) {
        return false; 
    }
    sheet_[index]->x_ = x;
    sheet_[index]->y_ = y;
    return true;
}
void StickerSheet::removeSticker (unsigned index) {
    Image* to_delete = sheet_[index];
    delete to_delete;
    to_delete = NULL;
    sheet_.erase(sheet_.begin() + index);
}
Image * StickerSheet::getSticker (unsigned index) {
    if (index >= sheet_.size()) {
        return NULL;
    } else if (index < 0) {
        return NULL;
    }
    return sheet_[index];
}
Image StickerSheet::render () const {
    Image rendered_(picture_);
    for (unsigned int k = 0; k < sheet_.size(); ++k) {
        unsigned int sticker_y = sheet_.at(k)->height() + sheet_.at(k)->y_;
        unsigned int sticker_x = sheet_.at(k)->width() + sheet_.at(k)->x_;
        if (sticker_y > rendered_.height()) {
            rendered_.resize(rendered_.width(), sticker_y);
        }
        if (sticker_x > rendered_.width()) {
            rendered_.resize(sticker_x, rendered_.height());
        }
        for (unsigned int i = 0; i < sheet_[k]->width(); ++i) {
            for (unsigned int j = 0; j < sheet_[k]->height(); ++j) {
                cs225::HSLAPixel &pixel = sheet_[k]->getPixel(i,j);
                if (pixel.a != 0) {
                    rendered_.getPixel(i + sheet_[k]->x_, j + sheet_[k]->y_) = pixel;
                }
            }
        }
    }
    return rendered_;
}