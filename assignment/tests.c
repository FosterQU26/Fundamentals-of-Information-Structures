#include <string.h>

#include "model.h"
#include "testrunner.h"
#include "tests.h"

void run_test_1() {
    model_init();
    set_cell_value(ROW_2, COL_A, strdup("-1.4"));
    assert_display_text(ROW_2, COL_A, strdup("-1.4"));
    assert_edit_text(ROW_2, COL_A, strdup("-1.4"));

    set_cell_value(ROW_2, COL_B, strdup("2.9"));
    assert_display_text(ROW_2, COL_B, strdup("2.9"));
    assert_edit_text(ROW_2, COL_B, strdup("2.9"));

    set_cell_value(ROW_2, COL_C, strdup("=A2+B2+0.4"));
    assert_display_text(ROW_2, COL_C, strdup("1.9"));
    assert_edit_text(ROW_2, COL_C, strdup("=A2+B2+0.4"));

}

void run_test_2() {
    model_init();
    set_cell_value(ROW_1,COL_A,strdup("1.9"));
    set_cell_value(ROW_2, COL_A, strdup("4.4"));
    set_cell_value(ROW_2, COL_C, strdup("=A1+A2+1"));

    assert_display_text(ROW_2, COL_C, strdup("7.3"));

    set_cell_value(ROW_1,COL_A,strdup("-1.9"));

    assert_display_text(ROW_2, COL_C, strdup("3.5"));
}

void run_test_3(){
    model_init();
    set_cell_value(ROW_1,COL_A,strdup("1.9"));
    set_cell_value(ROW_2, COL_A, strdup("4.4"));
    set_cell_value(ROW_2, COL_C, strdup("=A1+A2+1"));

    assert_display_text(ROW_2, COL_C, strdup("7.3"));

    set_cell_value(ROW_1,COL_A,strdup("=C2 + 1.1"));

    assert_display_text(ROW_1,COL_A,strdup("ERROR"));
}

void run_test_4 (){
    model_init();
    set_cell_value(ROW_1,COL_A,strdup("1"));
    set_cell_value(ROW_1,COL_B,strdup("3"));
    set_cell_value(ROW_2,COL_A,strdup("10"));
    set_cell_value(ROW_2,COL_B,strdup("2"));

    set_cell_value(ROW_3,COL_A,strdup("=SUM[A1:B2]"));
    assert_display_text(ROW_3,COL_A,strdup("16"));
    assert_edit_text(ROW_3,COL_A,strdup("=SUM[A1:B2]"));

    set_cell_value(ROW_3,COL_B,strdup("=AVG[A1:B2]"));
    assert_display_text(ROW_3,COL_B,strdup("4"));
    assert_edit_text(ROW_3,COL_B,strdup("=AVG[A1:B2]"));

    set_cell_value(ROW_3,COL_C,strdup("=MIN[A1:B2]"));
    assert_display_text(ROW_3,COL_C,strdup("1"));
    assert_edit_text(ROW_3,COL_C,strdup("=MIN[A1:B2]"));

    set_cell_value(ROW_3,COL_D,strdup("=MAX[A1:B2]"));
    assert_display_text(ROW_3,COL_D,strdup("10"));
    assert_edit_text(ROW_3,COL_D,strdup("=MAX[A1:B2]"));    
}

void run_test_5 (){
    model_init();
    set_cell_value(ROW_1,COL_A,strdup("7"));
    set_cell_value(ROW_1,COL_B,strdup("-1"));
    set_cell_value(ROW_2,COL_A,strdup("8"));
    set_cell_value(ROW_2,COL_B,strdup("10"));

    set_cell_value(ROW_3,COL_A,strdup("=SUM[A1:B2]"));
    set_cell_value(ROW_3,COL_B,strdup("=AVG[A1:B2]"));
    set_cell_value(ROW_3,COL_C,strdup("=MIN[A1:B2]"));
    set_cell_value(ROW_3,COL_D,strdup("=MAX[A1:B2]"));

    assert_display_text(ROW_3,COL_A,strdup("24"));
    assert_display_text(ROW_3,COL_B,strdup("6"));
    assert_display_text(ROW_3,COL_C,strdup("-1"));
    assert_display_text(ROW_3,COL_D,strdup("10"));

    set_cell_value(ROW_1,COL_B,strdup("11"));

    assert_display_text(ROW_3,COL_A,strdup("36"));
    assert_display_text(ROW_3,COL_B,strdup("9"));
    assert_display_text(ROW_3,COL_C,strdup("7"));
    assert_display_text(ROW_3,COL_D,strdup("11"));
}