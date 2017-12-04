.PHONY: clean All

All:
	@echo "----------Building project:[ UnrealatedLauncher - Debug ]----------"
	@"$(MAKE)" -f  "UnrealatedLauncher.mk"
clean:
	@echo "----------Cleaning project:[ UnrealatedLauncher - Debug ]----------"
	@"$(MAKE)" -f  "UnrealatedLauncher.mk" clean
