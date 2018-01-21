nasa_land/worm_hole >> /dev/null
for i in {1..50}; do sh sanpei.sh nasa_land > /tmp/output$i; done
diff -q --from-file /tmp/output{1..50}
