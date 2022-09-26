#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>

#include "toolgrp.h"
#include "dropwin.h"
#include "event_header.h"

#include <stdint.h>

static dropwin *win_main;    // The main window
static dockgroup *dock;      // the toolbar dock

static int tb_idx = 0;  // counts how many toolbars we have made
static char labels[32]; // Generic label strings...

#define TB_HEIGHT  DROP_REGION_HEIGHT

static void cb_Exit(Fl_Button*, void*)
{
	win_main->hide(); // hide the main window
	// do we have toolbars undocked? If so, find them and hide them...
	toolgrp::hide_all();
}

static void cb_Check(Fl_Button*, void*)
{
	dock->dock_check();
}

static void cb_generic(Fl_Button*, void* v)
{
	int idx = (intptr_t)v;
	printf("ToolGroup: %d\n", idx);
	fflush(stdout);
}

static void add_docked(Fl_Button*, void*)
{
	// Create a docked toolgroup
	toolgrp *tgroup = new toolgrp(dock, 0, 130, TB_HEIGHT);
	  Fl_Button* dm1 = new Fl_Button(24, 10, 44, 20);
	  tb_idx++;
	  sprintf(labels, "test %d", tb_idx);
	  dm1->copy_label(labels);
	  dm1->box(FL_THIN_UP_BOX);
	  dm1->callback((Fl_Callback*)cb_generic, (void *)(intptr_t)tb_idx);
	  dm1 = new Fl_Button(74, 10, 44, 20);
	  dm1->copy_label(labels);
	  dm1->box(FL_THIN_UP_BOX);
	  dm1->callback((Fl_Callback*)cb_generic, (void *)(intptr_t)tb_idx);
	tgroup->end();
	tgroup->box(FL_BORDER_BOX);
}

static void add_floater(Fl_Button*, void*)
{
	// create a floating toolbar window
	toolgrp *tool_group = new toolgrp(dock, 1, 140, 155, 180, TB_HEIGHT);
	  Fl_Button* dm2 = new Fl_Button(24, 10, 44, 20);
	  tb_idx++;
	  sprintf(labels, "test %d", tb_idx);
	  dm2->copy_label(labels);
	  dm2->box(FL_THIN_UP_BOX);
	  dm2->callback((Fl_Callback*)cb_generic, (void *)(intptr_t)tb_idx);
	  dm2 = new Fl_Button(74, 10, 44, 20);
	  dm2->copy_label(labels);
	  dm2->box(FL_THIN_UP_BOX);
	  dm2->callback((Fl_Callback*)cb_generic, (void *)(intptr_t)tb_idx);
	  dm2 = new Fl_Button(124, 10, 44, 20);
	  dm2->copy_label(labels);
	  dm2->box(FL_THIN_UP_BOX);
	  dm2->callback((Fl_Callback*)cb_generic, (void *)(intptr_t)tb_idx);
	tool_group->end(); 
	tool_group->box(FL_THIN_UP_BOX);
}

static Fl_Menu_Item menu_[] = {
 {"&Tools", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Add &Docked", FL_ALT + 'd',  (Fl_Callback*)add_docked, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Add &Floating", FL_ALT + 'f',  (Fl_Callback*)add_floater, 0, FL_MENU_DIVIDER, FL_NORMAL_LABEL, 0, 14, 0},
 {"E&xit", 0,  (Fl_Callback*)cb_Exit, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

int main(int argc, char **argv) 
{
	win_main = new dropwin(728, 420, "Main Window");
	
	{ Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, win_main->w(), 20);
      o->box(FL_FLAT_BOX);
      o->menu(menu_);
    } // Fl_Menu_Bar* o
    
	// Create a dock area in the main window
	dock = new dockgroup(1, 21,  win_main->w() - 2, TB_HEIGHT + 2);
	dock->box(FL_THIN_DOWN_BOX);
	dock->end();
	dock->set_window(win_main);

	// Create a toolgroup already docked in this dock
	add_docked(0, 0);
	dock->redraw();
	
	// Record in the dropwin which dock to use
	win_main->set_dock(dock);

	win_main->begin();
	// Contents area for the main window
	int y_off = 20 + TB_HEIGHT + 2;
	win_main->workspace = new Fl_Group(2, y_off, win_main->w() - 4, win_main->h() - 4 - y_off);
	win_main->workspace->box(FL_THIN_DOWN_BOX);
	win_main->workspace->color(FL_WHITE);
	{ Fl_Group* o = new Fl_Group(15, 130, 20, 20);
		o->end();
		win_main->workspace->resizable(o);
	} 
	{ Fl_Button* o = new Fl_Button(638, 365, 64, 20, "Exit");
		o->callback((Fl_Callback*)cb_Exit);
	} 
	{ Fl_Button* o = new Fl_Button(538, 365, 64, 20, "Check");
		o->callback((Fl_Callback*)cb_Check);
	} 
	win_main->workspace->end();
	win_main->workspace->tooltip("Application Area");

	win_main->end();

	// override the main window exit callback to ensure that
	// we delete any exposed toolgrps when the main window exits
	win_main->callback((Fl_Callback*)cb_Exit);
	
	// Set the resizeable for the main window
	win_main->resizable(win_main->workspace);
	
	// Show the main window
	win_main->show(argc, argv);

	// create a floating toolbar window - if you do this before the main
	// window is shown, the non-modal tool window may not parent correctly
	// it still works, but the modality may be awry...
	add_floater(0, 0);

	// Now expose all the non-docked tool windows - not really necessary
	toolgrp::show_all();

	// and run...
	return Fl::run();
}

/* End of File */
