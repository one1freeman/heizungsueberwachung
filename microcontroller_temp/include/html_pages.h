#ifndef HTML_PAGES_H
#define HTML_PAGES_H

const char SETUP_PAGE[] PROGMEM = R"rawString(
<!DOCTYPE html>
<html lang="de">
    <head>
        <meta charset="UTF-8">
        <title>Setup Page</title>
    </head>
    <body>
        <h1>Willkommen zur Setup-Seite</h1>
        <form action="/submit" method="POST">
            <label for="ssid">SSID:</label><br>
            <input type="text" id="ssid" name="ssid"><br>
            <label for="pass">Passwort:</label><br>
            <input type="text" id="pass" name="pass"><br>
            <label for="id">Geräte-ID:</label><br>
            <input type="text" id="id" name="id"><br>
            <input type="submit" value="Absenden">
        </form>
        %s
    </body>
</html>
)rawString";

#endif