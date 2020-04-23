package server;
import java.util.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Scanner;

// реализуем интерфейс Runnable, который позволяет работать с потоками
public class ClientHandler implements Runnable {


    // экземпляр нашего сервера
    private Server server;
    // исходящее сообщение
    private PrintWriter outMessage;
    // входящее собщение
    private Scanner inMessage;
    private static final String HOST = "localhost";
    private static final int PORT = 3443;
    // клиентский сокет
    private Socket clientSocket = null;
    // количество клиента в чате, статичное поле
    private static int clients_count = 0;

    // конструктор, который принимает клиентский сокет и сервер
    public ClientHandler(Socket socket, Server server) {
        try {
            clients_count++;
            this.server = server;
            this.clientSocket = socket;
            this.outMessage = new PrintWriter(socket.getOutputStream());
            this.inMessage = new Scanner(socket.getInputStream());
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
    // Переопределяем метод run(), который вызывается когда
    // мы вызываем new Thread(client).start();
    @Override
    public void run() {
        Map<String, String> termins = new HashMap<String, String>();
        termins.put("телефон", "Система технических приспособлений для передачи звуков на расстояние по проводам при помощи электрической энергии.");
        termins.put("компьютер", "Электронно-вычислительная машина (ЭВМ).");
        int n;
        try {
            while (true) {
                // сервер отправляет сообщение

                server.sendMessageToAllClients("Клиентов в чате = " + clients_count);
                break;
            }

            while (true) {
                // Если от клиента пришло сообщение
                if (inMessage.hasNext()) {
                    String clientMessage = inMessage.nextLine();
                    String clientMessage1="";
                    if(clientMessage.equalsIgnoreCase("телефон"))clientMessage1="Телефон - Система технических приспособлений для передачи звуков на расстояние по проводам при помощи электрической энергии.";
                    if(clientMessage.equalsIgnoreCase("компьютер"))  clientMessage1="Компьютер - Электронно-вычислительная машина (ЭВМ).";
                    if(clientMessage.equalsIgnoreCase("микрофон"))  clientMessage1="Микрофон -Прибор, преобразующий звуковые колебания в электрические для передачи звуков на расстояние.";
                    if(clientMessage.equalsIgnoreCase("наушники"))  clientMessage1="Наушники - два телефона с оголовьем, предназначенные для подключения к бытовым радиоэлектронным аппаратам.";
                    // если клиент отправляет данное сообщение, то цикл прерывается и
                    // клиент выходит из чата
                    if (clientMessage.equalsIgnoreCase("##session##end##")) {
                        break;
                    }
                    // выводим в консоль сообщение (для теста)

                    // отправляем данное сообщение всем клиентам
                    System.out.println(clientMessage1);
                    server.sendMessageToAllClients(clientMessage1);
                }
                // останавливаем выполнение потока на 100 мс
                Thread.sleep(100);
            }
        }
        catch (InterruptedException ex) {
            ex.printStackTrace();
        }
        finally {
            this.close();
        }
    }
    // отправляем сообщение
    public void sendMsg(String msg) {
        try {
            outMessage.println(msg);
            outMessage.flush();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
    // клиент выходит из чата
    public void close() {
        // удаляем клиента из списка
        server.removeClient(this);
        clients_count--;
        server.sendMessageToAllClients("Клиентов в чате = " + clients_count);
    }
}
