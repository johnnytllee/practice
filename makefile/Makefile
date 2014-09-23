PWD := $(shell pwd)
SUBST := $(subst /johnny,/johnny /, $(PWD))
WORD1 := $(word 1, $(SUBST))
WORD2 := $(word 2, $(SUBST))
PROJECT_ROOT := $(word 1, $(subst /johnny,/johnny /,$(shell pwd)))

all:
	@echo $(PWD)
	@echo $(SUBST)
	@echo $(WORD1)
	@echo $(WORD2)
	@echo ${PROJECT_ROOT}
ifeq "$(CFG)" "true"
	echo $(CFG) = true
else
	echo $(CFG) = false
endif
