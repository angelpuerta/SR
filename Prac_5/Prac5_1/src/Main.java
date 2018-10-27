import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.jline.terminal.Terminal;
import org.jline.terminal.TerminalBuilder;
import org.jline.utils.NonBlockingReader;

public class Main {

	public static void main(String[] args) throws InterruptedException, IOException {
		Comunicador comunicador = new Comunicador();
		comunicador.listarPuertos();

		comunicador.conectarse("COM3");

		comunicador.inicializarEscucha();

		SesionRecord record = new SesionRecord(comunicador);
		record.execute();

		comunicador.cerrarESyDesconectar();

	}

}