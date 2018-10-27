import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEventListener;
import gnu.io.SerialPortEvent;
import java.util.TooManyListenersException;

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.util.Enumeration;
import java.util.HashMap;

public class Comunicador implements SerialPortEventListener {

	static HashMap<String, CommPortIdentifier> mapaPuertos = new HashMap<String, CommPortIdentifier>();

	public void listarPuertos() {
		CommPortIdentifier idPuerto;
		Enumeration enumPuertos = CommPortIdentifier.getPortIdentifiers();
		while (enumPuertos.hasMoreElements()) {
			idPuerto = (CommPortIdentifier) enumPuertos.nextElement();
			if (idPuerto.getPortType() == CommPortIdentifier.PORT_SERIAL) {
				System.out.println(idPuerto.getName());
				mapaPuertos.put(idPuerto.getName(), idPuerto);
			}
		}
	}

	// Puerto de Conexión
	private SerialPort puertoSerial;

	public void conectarse(String nombrePuerto) {
		CommPortIdentifier selectedPortIdentifier = (CommPortIdentifier) mapaPuertos.get(nombrePuerto);
		try {
			// open para abrir el puerto
			puertoSerial = (SerialPort) selectedPortIdentifier.open("ControlPC", 2000);
			// TimeOut
		} catch (PortInUseException e) {
			System.out.println("Error A Puerto en uso " + e.getMessage());
		} catch (Exception e) {
			System.out.println("Error B " + e.getMessage());
		}
	}

	private InputStream input = null;
	private OutputStream output = null;

	public void inicializarES() {
		try {
			//
			input = puertoSerial.getInputStream();
			output = puertoSerial.getOutputStream();
		} catch (IOException e) {
			System.out.println("Error C " + e.getMessage());
		}
	}

	public void escribir(String texto) {
		try {
			output.write(texto.getBytes());
		} catch (IOException e) {
			System.out.println("Error D " + e.getMessage());
		}
	}

	public void cerrarESyDesconectar() {
		try {
			puertoSerial.removeEventListener();
			puertoSerial.close();
			input.close();
			output.close();
		} catch (Exception e) {
			System.out.println("Error E " + e.getMessage());
		}
	}

	String lectura = "";

	@Override
	public void serialEvent(SerialPortEvent arg0) {
		if (arg0.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
			try {
				byte byteLeido = (byte) input.read();
				lectura += new String(new byte[] { byteLeido });
				if (new String(new byte[] { byteLeido }).equals("\n")) {
					System.out.println("Arduino dice: " + lectura);
					lectura = "";
				}
			} catch (Exception e) {
				System.out.println("Error F " + e.getMessage());
			}
		}
	}
	
	

	public String getLectura() {
		return lectura;
	}

	public void inicializarEscucha() {
		try {
			puertoSerial.addEventListener(this);
			puertoSerial.notifyOnDataAvailable(true);
		} catch (TooManyListenersException e) {
			System.out.println("Error G " + e.getMessage());
		}
	}

}