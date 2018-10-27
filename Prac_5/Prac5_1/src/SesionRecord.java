import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

import javax.naming.CommunicationException;

import command.Command;
import command.Move;

public class SesionRecord {

	public static final int MAX_POSITION = 24;

	public static final int SIZE_STORED_COMMANDS = 100;

	public static final String REPRODUCE_MOVEMENT = "REPRODUCIR_MOVIMIENTO";
	public static final String RECORD_MOVEMENT = "GRABAR_MOVIMIENTO";
	public static final String FREE_MOVEMENT = "LIBRE_MOVIMIENTO";

	public static final String MOVE = "MOVER";
	public static final String WAIT = "PARAR";

	public static final String CHANGE_MODE_CHARACTER = "y";

	private BufferedReader bufferedReader;
	private Command[] commands;
	private int position;
	private Comunicador comunicador;

	public SesionRecord(Comunicador comunicador) {
		bufferedReader = new BufferedReader(new InputStreamReader(System.in));
		commands = new Command[SIZE_STORED_COMMANDS];
		this.comunicador = comunicador;
	}

	void addCommand(Command command) {
		commands[position] = command;
		position = position % SIZE_STORED_COMMANDS;
	}

	String consumeCommand() {
		position = (position - 1) % SIZE_STORED_COMMANDS;
		return commands[position].generateInstruction();
	}

	void resetCommands() {
		position = 0;
		commands = new Command[SIZE_STORED_COMMANDS];
	}

	public void execute() {
		System.out.println("Para grabar la sesión pulse Y");
		if (!isChangeCharacterPressed())
			freeMode();
		else
			recordMode();
	}

	// TODO Cambiar por state si hay más modos
	void reproduceMode() {
		System.out.println("Para dejar de reproducir los movimientos pulse Y");
		comunicador.escribir(REPRODUCE_MOVEMENT);
		while (position != 0 && !isChangeCharacterPressed()) {
			comunicador.escribir(consumeCommand());
		}
		resetCommands();
		freeMode();
	}

	void freeMode() {
		System.out.println("Para grabar la sesión pulse Y");
		comunicador.escribir(FREE_MOVEMENT);
		while (!isChangeCharacterPressed())
			;
		recordMode();
	}

	void recordMode() {
		System.out.println("Para dejar de grabar la sesión pulse Y");
		comunicador.escribir(RECORD_MOVEMENT);
		while (isChangeCharacterPressed()) {
			String lectura = comunicador.getLectura();
			parseBuffer(lectura);
		}
		freeMode();
	}

	void parseBuffer(String buffer) {
		for (String command : buffer.split(";")) {
			parseCommand(command);
		}
	}

	boolean parseCommand(String command) {
		String aux[] = command.trim().split(",");

		if (aux.length != 2 || aux[0].isEmpty() || aux[1].isEmpty())
			return false;

		try {
			addCommand(new Move(Integer.parseInt(aux[0]), Long.parseLong(aux[1])));
			return true;

		} catch (NumberFormatException e) {
			return false;
		}
	}

	boolean isChangeCharacterPressed() {
		try {
			return bufferedReader.ready() && bufferedReader.readLine().trim().contains(CHANGE_MODE_CHARACTER);
		} catch (IOException e) {
			System.err.println("Defecto al procesar el buffer");
			return false;
		}
	}

}
