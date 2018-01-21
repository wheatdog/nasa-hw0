make -C nasa_land/
shc -f sanpei.sh -o sanpei

mkdir -p nasa_land/village/bookshelf
nasa_land/worm_hole
find sanpei nasa_land/castle/{boss,.seed} nasa_land/cave/{goblin,chest} nasa_land/shop/{.seed,list,merchant} nasa_land/village/bookshelf/* nasa_land/village/wisdom nasa_land/worm_hole > pack_list
tar zcvf challenge.tar.gz -T pack_list
