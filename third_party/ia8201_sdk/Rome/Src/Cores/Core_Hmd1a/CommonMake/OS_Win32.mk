# standard *nix like tools
MAKE_DIR		:= mkdir
COPY			:= xcopy
MOVE			:= rename
REMOVE			:= del /f /q
REMOVE_DIR		:= rmdir /q
REMOVE_RECURSE	:= rm /s /q

define clean_object
	@echo Cleaning Object Directory $(BIN_PATH)
	@if exist $(subst /,\,$(BIN_PATH))\*.o $(REMOVE) $(subst /,\,$(BIN_PATH))\*.o
	@if exist $(subst /,\,$(BIN_PATH)) $(REMOVE_DIR) $(BIN_PATH)
endef

define clean_target
	@echo Cleaning Target $(TARGET)
	@if exist $(subst /,\,$(TARGET)) $(REMOVE) $(subst /,\,$(TARGET))
endef

# 1=Target, 2=Objects, 3=Libraries

define archive_target
	@echo archiving: $(1)
	@$(AR) -cr $(1) $(2)
endef

define build_target
	@echo linking: $(1)
	$(CPP) $(2) $(3) $(CFLAGS) $(LD_FLAGS) -o $(1)
endef

define build_object
	@echo Compiling $(2)
	@if not exist $(BIN_PATH) $(MAKE_DIR) $(BIN_PATH)
	$(CPP) -c $(CFLAGS) $(INCLUDE) $(2) -o $(1)
endef

define copy_file
	@$(COPY) /F /Y $(subst /,\,$(1)) $(subst /,\,$(2))
endef
