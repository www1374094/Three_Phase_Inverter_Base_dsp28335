################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
HAL/TPVSI_DSP28335_BSP.obj: ../HAL/TPVSI_DSP28335_BSP.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="E:/Code/Three_Phase_Inverter_Base_dsp28335/HAL" --include_path="E:/Code/Three_Phase_Inverter_Base_dsp28335" --include_path="E:/Code/Three_Phase_Inverter_Base_dsp28335/include" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="HAL/TPVSI_DSP28335_BSP.d" --obj_directory="HAL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HAL/TPVSI_DSP28335_HAL.obj: ../HAL/TPVSI_DSP28335_HAL.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="E:/Code/Three_Phase_Inverter_Base_dsp28335/HAL" --include_path="E:/Code/Three_Phase_Inverter_Base_dsp28335" --include_path="E:/Code/Three_Phase_Inverter_Base_dsp28335/include" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="HAL/TPVSI_DSP28335_HAL.d" --obj_directory="HAL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


