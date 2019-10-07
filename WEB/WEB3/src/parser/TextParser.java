package parser;

import model.Text;
import model.text_unit.text.TextUnit;

import java.util.ArrayList;

/**
 * paragraph text splitter parser
 */
public class TextParser {

    /**
     * next splitter
     */
    private ParagraphTextParser nextSplitter;


    public TextParser() {
        nextSplitter = new ParagraphTextParser();
    }

    /**
     * split text codeBlock and paragraph
     * @param textString text
     * @return return Text object
     */
    public Text splitText(String textString) {
        Text text = new Text();
        ArrayList<TextUnit> result;
        try {
            result = nextSplitter.split(trim(textString));
        } catch (Exception e) {
            throw e;
        }

        text.setText(result);
        return text;
    }

    /**
     * replace tabs
     * @param text text
     * @return replaced text
     */
    protected String trim(String text){
        text = text.trim();
        text = text.replaceAll( "[\t ]+", " ");
        return text;
    }

}
