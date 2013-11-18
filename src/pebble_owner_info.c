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
Layer layer_contact_info;
TextLayer layer_company;
TextLayer layer_name;
TextLayer layer_contact;
TextLayer layer_button;

Layer layer_QR;
BmpContainer image;

//QR Layer handler
void layer_update_callback(Layer *me, GContext * ctx){
  GRect destination = layer_get_frame(&image.layer.layer);

  destination.origin.y = 0;
  destination.origin.x = 0;

  graphics_draw_bitmap_in_rect(ctx, &image.bmp, destination);
}

// void contact_layer_update_callback(Layer *me, GContext * ctx){

// }

//Click handlers
void clickHandlerQR(ClickRecognizerRef recognizer, Window *window){
  layer_set_hidden(&layer_QR, false);
  layer_set_hidden(&layer_contact_info, true);
}

void goBack(){
  layer_set_hidden(&layer_contact_info, false);
  layer_set_hidden(&layer_QR, true);
}

void clickHandlerBack(ClickRecognizerRef recognizer, Window *window){
  goBack();
}



void click_config_provider(ClickConfig **config, Window *window) {
  config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) clickHandlerQR;
  //config[BUTTON_ID_DOWN]->long_click.handler = (ClickHandler) clickHandlerBack;
  config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 1;
  
  config[BUTTON_ID_UP]->click.handler = (ClickHandler) clickHandlerBack;
  config[BUTTON_ID_UP]->click.repeat_interval_ms = 10;

  config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) clickHandlerBack;
  config[BUTTON_ID_SELECT]->click.repeat_interval_ms = 10;


}



void handle_init(AppContextRef ctx) {

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);

  //layer_contact_info.update_proc = &contact_layer_update_callback;
  //Company information
  text_layer_init(&layer_company, GRect(0, 20, 144, 30));
  text_layer_set_text_alignment(&layer_company, GTextAlignmentCenter);
  text_layer_set_text(&layer_company, "Aaltonen Interactive\nCEO / Web Specialist");
  text_layer_set_font(&layer_company, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(&layer_contact_info, &layer_company.layer);

  //Name
  text_layer_init(&layer_name, GRect(0, 60, 144, 30));
  text_layer_set_text_alignment(&layer_name, GTextAlignmentCenter);
  text_layer_set_text(&layer_name, "Joni Aaltonen");
  text_layer_set_font(&layer_name, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  layer_add_child(&layer_contact_info, &layer_name.layer);

  //Contact information
  text_layer_init(&layer_contact, GRect(0, 100, 144, 30));
  text_layer_set_text_alignment(&layer_contact, GTextAlignmentCenter);
  text_layer_set_text(&layer_contact, "joni@aaltointeractive.fi\n+358 40 700 5372");
  text_layer_set_font(&layer_contact, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(&layer_contact_info, &layer_contact.layer);

  //button text
  text_layer_init(&layer_button, GRect(100, 132, 40, 30));
  text_layer_set_text_alignment(&layer_button, GTextAlignmentRight);
  text_layer_set_text(&layer_button, "QR");
  text_layer_set_font(&layer_button, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(&layer_contact_info, &layer_button.layer);

  //add contact info layer to window
  layer_add_child(&window.layer, &layer_contact_info);

  //button functionality
  window_set_click_config_provider(&window, (ClickConfigProvider) click_config_provider);

  //QR Image
  layer_init(&layer_QR, window.layer.frame);
  layer_QR.update_proc = &layer_update_callback;  
  layer_add_child(&window.layer, &layer_QR);
  layer_set_hidden(&layer_QR, true);
  resource_init_current_app(&VERSION);
  bmp_init_container(RESOURCE_ID_QR_CONTACT_INFO, &image);

}

void handle_deinit(AppContextRef ctx){
  bmp_deinit_container(&image);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit
  };
  app_event_loop(params, &handlers);
}
