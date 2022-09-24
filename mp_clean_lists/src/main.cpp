#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

int main() {
    List<int> list;

    for (int i = 1; i <= 10; i++)
        list.insertBack(i);

    list.tripleRotate();

    stringstream s;

    list.print(s);

    return 0;
}