package view;

import controller.Controller;
import localization.LocaleHelper;
import model.Text;

import java.io.IOException;

import static localization.LocaleHelper.*;

/**
 * Main class which run controller's demonstrate method
 */
public class Main {

    private static final String ANSI_GREEN = "\u001B[32m";
    private static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_RED = "\u001B[31m";

    /**
     * main method
     *
     * @param args argument lines
     */
    public static void main(String[] args) {
        Controller controller = new Controller();
        try {
            String result = controller.loadText("src\\input.txt");
            System.out.println(ANSI_GREEN + "------" + LocaleHelper.getLocalizedString(LocaleHelper.FILE_LOADED) + "------" + ANSI_RESET);
            System.out.println(result);
            System.out.println();
            System.out.println();

            System.out.print(ANSI_GREEN + "------" + (LocaleHelper.getLocalizedString(START_COMBINE)) + "------" + ANSI_RESET);
            Text text = controller.parseTextStringToText();
            System.out.println(text.toString());
            System.out.println();

            System.out.print(ANSI_GREEN + "------" + (LocaleHelper.getLocalizedString(SORT)) + "------" + ANSI_RESET);
            System.out.println(controller.sortWords(text).toString());
            System.out.println();

            System.out.print(ANSI_GREEN + "------" + (LocaleHelper.getLocalizedString(DELETE_NEXT)) + "------" + ANSI_RESET);
            System.out.println(controller.deleteNext(text).toString());
            System.out.println();

        } catch (ArrayIndexOutOfBoundsException ex) {
            System.out.println();
            ex.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
