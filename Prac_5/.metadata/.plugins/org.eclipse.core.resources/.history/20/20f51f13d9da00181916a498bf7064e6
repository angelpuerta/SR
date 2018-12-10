public class Main {

	public static void main(String[] args) {
		Comunicador comunicador = new Comunicador();
		comunicador.listarPuertos();

		comunicador.conectarse("COM3");

		comunicador.inicializarEscucha();

		SesionRecord record = new SesionRecord(comunicador);
		record.execute();

		comunicador.cerrarESyDesconectar();

	}

}