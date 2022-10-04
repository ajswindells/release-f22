#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = NULL;
  current_ = Point(0,0);
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point& start, double& tolerance, PNG& png) {
  /** @todo [Part 1] */
  traversal_ = traversal;
  start_ = start;
  tolerance_ = tolerance;
  png_ = png;
  current_ = traversal_->peek();
  visitedList.resize(png.width()*png.height(), false);
}

bool ImageTraversal::Iterator::visited(const Point& current) {
  return visitedList[current.x + current.y * png_.width()];
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (!traversal_->empty()) {
    visitedList[current_.x + current_.y * png_.width()] = true;
    traversal_->pop();
    Point right = Point(current_.x + 1, current_.y);
    Point down = Point(current_.x, current_.y + 1);
    Point left = Point(current_.x - 1, current_.y);
    Point up = Point(current_.x, current_.y - 1);
   
    while (!traversal_->empty() && visited(Point(traversal_->peek().x, traversal_->peek().y))) {
      current_ = traversal_->pop();
    }
    TraversalAdd(right);
    TraversalAdd(down);
    TraversalAdd(left);
    TraversalAdd(up);
  }
  if (!traversal_->empty()) {
    current_ = traversal_->peek();
  }
  return *this;
}

void ImageTraversal::Iterator::TraversalAdd(Point dir) {
  if (dir.x < png_.width() && dir.y < png_.height()) {
      if (calculateDelta(png_.getPixel(dir.x, dir.y), png_.getPixel(start_.x, start_.y)) <= tolerance_ && !visited(dir)) {
        traversal_->add(dir);
      }
    }
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool this_empty = false;
  bool other_empty = false;
  if (traversal_ == NULL) {
    this_empty = true;
  }
  if (other.traversal_ == NULL) {
    other_empty = true;
  }
  if (this_empty == false) {
    this_empty = traversal_->empty();
  }
  if (other_empty == false) {
    other_empty = other.traversal_->empty();
  }
  return !(this_empty && other_empty);
}

