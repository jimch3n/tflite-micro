# standard *nix like tools
MAKE_DIR		:= mkdir -p
COPY			:= cp
MOVE			:= mv
REMOVE			:= rm -f
REMOVE_DIR		:= rmdir
REMOVE_RECURSE	:= rm -rf

define clean_object
	@echo Cleaning Object Directory $(BIN_PATH)
	@if test -d $(subst \,/,$(BIN_PATH)); then $(REMOVE) $(subst \,/,$(BIN_PATH))/*.o; fi;
	@if test -d $(subst \,/,$(BIN_PATH)); then $(REMOVE_DIR) $(subst \,/,$(BIN_PATH)); fi;
endef

define clean_target
	@echo Cleaning Target $(TARGET)
	@if test $(subst \,/,$(TARGET)); then $(REMOVE) $(subst \,/,$(TARGET)); fi;
endef

# 1=Target, 2=Objects, 3=Libraries

define archive_target
	@echo archiving: $(1)
	$(AR) -cr $(1) $(2)
endef

define build_target
	@echo linking: $(1)
	$(CPP) $(2) $(3) $(CFLAGS) $(LD_FLAGS) -o $(1)
endef

define build_object
	@echo Compiling $(2)
	@if test -d $(BIN_PATH); then echo; else $(MAKE_DIR) $(BIN_PATH); fi;
	$(CPP) -c $(CFLAGS) $(INCLUDE) $(2) -o $(1)
endef

define copy_file
	@$(COPY) -v -f $(subst \,/,$(1)) $(subst \,/,$(2))
endef

