package controller;

import localization.LocaleHelper;
import model.Text;
import model.exception.FileException;
import model.exception.InvalidParsingException;
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
     * @throws FileException if no file
     */
    public String loadText(String path) throws FileException {
        try {
            byte[] encoded = Files.readAllBytes(Paths.get(path));
            textString = new String(encoded, Charset.forName("windows-1251"));
        } catch (IOException e) {
            throw new FileException(LocaleHelper.getLocalizedString(LocaleHelper.INVALID_ARGS), e);
        }
        return textString;
    }

    /**
     * parse text string to text object
     *
     * @return text object
     */
    public Text parseTextStringToText() throws InvalidParsingException {
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
    public List sortWords(Text text) {
        List sorted;
        try {
            sorted = text.sortWordsAccordingToAmountOfEntries();
        } catch (Exception e) {
            throw e;
        }
        return sorted;
    }

    public Text DeleteNext(Text text) {
        Text temp = text;
        temp.DeleteCharacters(true);
        return temp;
    }

    public Text DeletePrevious(Text text) {
        Text temp = text;
        temp.DeleteCharacters(false);
        return temp;
    }
}