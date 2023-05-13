#include "item.h"

Item::Item(char c): Object(c, 'I'), used{false} {

}

bool Item::isUsed() {
    return used;
}
