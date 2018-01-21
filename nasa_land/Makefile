all: castle/boss village/wisdom shop/merchant cave/goblin worm_hole

nasa.o: nasa.c nasa.h
	gcc $^ -I. -c

castle/boss: castle/boss.c nasa.o nasa.h
	gcc $^ -I. -o $@

village/wisdom: village/wisdom.c nasa.o nasa.h
	gcc $^ -I. -o $@

shop/merchant: shop/merchant.c nasa.o nasa.h
	gcc $^ -I. -o $@

cave/goblin: cave/goblin.c nasa.o nasa.h
	gcc $^ -I. -o $@

worm_hole: worm_hole.c nasa.o nasa.h
	gcc $^ -I. -o $@
