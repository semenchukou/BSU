package model.text_unit.text.part;

import model.text_unit.text.TextUnit;
import model.text_unit.text.TextUnitTypeEnum;

/**
 * Word
 */
public class Word extends TextUnit {

    public static final String WORD_NAME = "WORD";
    public static final String DIVIDER = ",:;'\"";
    public static final String PATTERN = "[^ " + Paragraph.DIVIDER + Sentence.DIVIDER + DIVIDER +  "]+";

    /**
     * word value getter
     * @return word
     */
    public String getText() {
        return text;
    }

    /**
     * word value
     */
    private String text;

    /**
     * constructor
     * @param text word value
     *
     */
    public Word(String text) {
        super(text, TextUnitTypeEnum.WORD);
        this.text = text;
    }

    @Override
    public String toString() {
        return text;
    }

    public void removeNext() {
        char first = text.charAt(0);
        text = text.replaceAll(Character.toString(first).toLowerCase(), "");
        text = text.replaceAll(Character.toString(first).toUpperCase(), "");
        text = first + text;
    }

    public void removePrevious() {
        char last = text.charAt(text.length() - 1);
        text = text.replaceAll(Character.toString(last).toLowerCase(), "");
        text = text.replaceAll(Character.toString(last).toUpperCase(), "");
        text = text + last;
    }
}
