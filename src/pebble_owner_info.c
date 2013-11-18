#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x14, 0x4F, 0x04, 0x17, 0x96, 0x0D, 0x4D, 0xC7, 0xB1, 0x92, 0x0B, 0x64, 0xB0, 0x0B, 0x1F, 0x5A }
PBL_APP_INFO(MY_UUID,
             "Owner Info", "Aaltonen Interactive",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer layer_company;
TextLayer layer_name;
TextLayer layer_contact;

void handle_init(AppContextRef ctx) {

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);

  text_layer_init(&layer_company, GRect(0, 20, 144, 30));
  text_layer_set_text_alignment(&layer_company, GTextAlignmentCenter);
  text_layer_set_text(&layer_company, "<company name>\n<title>");
  text_layer_set_font(&layer_company, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(&window.layer, &layer_company.layer);

  text_layer_init(&layer_name, GRect(0, 60, 144, 30));
  text_layer_set_text_alignment(&layer_name, GTextAlignmentCenter);
  text_layer_set_text(&layer_name, "<full name>");
  text_layer_set_font(&layer_name, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  layer_add_child(&window.layer, &layer_name.layer);

  text_layer_init(&layer_contact, GRect(0, 100, 144, 30));
  text_layer_set_text_alignment(&layer_contact, GTextAlignmentCenter);
  text_layer_set_text(&layer_contact, "<email address>\n<phone number>");
  text_layer_set_font(&layer_contact, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(&window.layer, &layer_contact.layer);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
