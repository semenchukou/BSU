package controller;

import model.Text;
import model.text_unit.text.TextUnit;
import parser.TextParser;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class Controller {

    private String textString;

    public String getTextString() {
        return textString;
    }

    /**
     * load text
     *
     * @param path path to file
     * @return text string
     */
    public String loadText(String path) throws IOException {
        try {
            byte[] encoded = Files.readAllBytes(Paths.get(path));
            textString = new String(encoded, Charset.forName("windows-1251"));
        } catch (IOException e) {
            throw e;
        }
        return textString;
    }

    /**
     * parse text string to text object
     *
     * @return text object
     */
    public Text parseTextStringToText(){
        TextParser textParser = new TextParser();
        Text parsedText;
        try {
            parsedText = textParser.splitText(textString);
        } catch (Exception e) {
            throw e;
        }
        return parsedText;
    }

    /**
     * Sort words according to amount of entries
     *
     * @param text text
     * @return list of words
     */
    public List<TextUnit> sortWords(Text text) {
        List sorted;
        try {
            sorted = text.sortWordsAccordingToAmountOfEntries();
        } catch (Exception e) {
            throw e;
        }
        return sorted;
    }

    public Text deleteNext(Text text) {
        Text temp = text;
        temp.deleteCharacters(true);
        return temp;
    }

    public Text deletePrevious(Text text) {
        Text temp = text;
        temp.deleteCharacters(false);
        return temp;
    }
}
