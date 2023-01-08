
// HTML boilerplate
const String html_start = "<!DOCTYPE html><html>"\
                      "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"\
                      "<link rel=\"icon\" href=\"data:,\">";


// LED toggle button
const String toggle = "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LEDs\" style=\"margin: 1.5em\"></form>";

// HTML for Colour Form
String form(int r, int g, int b) {
  String form_start = "<form action=\"/col\" method=\"POST\"></br>";
  String str_r = "<input type=\"range\" class=\"slider sl_r\" name=\"col_r\" id=\"col_r\" min=\"0\" max=\"255\" value=" + String(r) + "></br>";
  String str_g = "<input type=\"range\" class=\"slider sl_g\" name=\"col_g\" id=\"col_g\" min=\"0\" max=\"255\" value=" + String(g) + "></br>";
  String str_b = "<input type=\"range\" class=\"slider sl_b\" name=\"col_b\" id=\"col_b\" min=\"0\" max=\"255\" value=" + String(b) + "></br>";
  //String brite = "Brightness</br><input type=\"range\" class=\"slider sl_brightness\" name=\"bright\" id=\"bright\" min=\"0\" max=\"255\" value=" + String(brightness) + "></br>";
  String form_end = "<input type=\"submit\" id=\"setCol\" value=\"Set Colours\"></form>";

  return form_start + str_r + str_g + str_b + form_end;
}


// Styles
const String styles = "<style>"\
                     "html { font-family: Helvetica; background: #403F4C; color: white; display: inline-block; margin: 0px auto; text-align: center; font-size: 30px;}"\  
                     "input[type=submit]{background-color: #3185FC; border: none; color: white; padding: 8px 20px; text-align: center; text-decoration: none; display: inline-block; margin: 2px 4px; border-radius: 10px; font-size: 30px;}"\                                               
                     "input[type=number]{font-size: 30px; border-radius: 0.4em; text-align: center}"\
                     ".slider{width: 70%; -webkit-appearance: none; height: 1em; border-radius: 100em; margin: 2em}"\
                     ".slider::-webkit-slider-thumb{-webkit-appearance: none; width:2em; height: 2em; appearance: none; cursor:pointer; background: white; border-radius: 100em}"\
                     ".sl_r{background: red} .sl_g{background: #66ff66} .sl_b{background: #0055ff} .sl_brightness{background: #ffff66}"\
                     "</style></head>";

// JS for dynamic button colour
const String JS = "<script>\n"\
                    "document.getElementById(\"col_r\").oninput = function() {colChange()};\n"\
                    "document.getElementById(\"col_g\").oninput = function() {colChange()};\n"\
                    "document.getElementById(\"col_b\").oninput = function() {colChange()};\n"\
                    "function colChange() {\n"\
                      "var col_r = document.getElementById(\"col_r\").value;\n"\
                      "var col_g = document.getElementById(\"col_g\").value;\n"\
                      "var col_b = document.getElementById(\"col_b\").value;\n"\
                      "var el = document.getElementById(\"setCol\");\n"\
                      "setColour(el, \"rgb(\"+col_r+\",\"+col_g+\",\"+col_b+\")\");\n"\
                    "};\n"\
                    "function setColour(element, col) {\n"\
                      "element.style.backgroundColor = col;\n"\
                    "};\n"\
                  "</script>\n";
                       
// Make the overall string for the server to display
String the_page(int r, int g, int b) {
  return html_start + styles + "<body>" + toggle + form(r, g, b) + "</body>" + JS;
}
