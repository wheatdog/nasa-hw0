#!/bin/sh

LAND=$(dirname $0)/nasa_land

{
echo -n "cave: "
cat $LAND/cave/chest && echo

echo -n "village: "
basename $(du -b $LAND/village/bookshelf/* | sort -n -r | head -n1 | awk '{print $2}')

echo -n "shop: "
sed -e 's/poison/potion/' $LAND/shop/list | $LAND/shop/merchant | tail -n1 | cut -d" " -f 6

echo -n "castle: "
yes hit | $LAND/castle/boss | tail -n 1 | cut -d " " -f 4
} 2> /dev/null
