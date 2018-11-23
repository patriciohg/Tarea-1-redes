SRC1=echoClientSrc


default: all

all:
	@cd $(SRC1) && make


clean:
	@cd $(SRC1) && make clean
	@rm -rf *~

distclean: clean
	@cd $(SRC1) && make distclean


.PHONY: all clean distclean
