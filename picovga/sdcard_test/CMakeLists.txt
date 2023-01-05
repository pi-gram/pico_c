aux_source_directory(. DIR_SDCARDTEST_SRCS)

include_directories(../lib/fatfs)
include_directories(../lib/sdcard)

add_library(sdcard_test ${DIR_SDCARDTEST_SRCS})
target_link_libraries(sdcard_test PUBLIC pico_stdlib hardware_spi hardware_gpio hardware_pio fatfs sdcard fatfs sdcard)

