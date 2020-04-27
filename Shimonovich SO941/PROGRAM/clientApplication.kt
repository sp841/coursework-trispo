import java.io.*
import java.net.Socket
import java.net.UnknownHostException
import java.util.*

fun main(args: Array<String>) {
    val socket = Socket("localhost", 3345)
    val br: BufferedReader = BufferedReader(InputStreamReader(System.`in`))
    val dos: DataOutputStream = DataOutputStream(socket.getOutputStream())
    val dis: DataInputStream = DataInputStream(socket.getInputStream())
    try {
        println("Client connected to socket")
        println()
        println("Client writing channel = oos & reading channel = dis initialized.")

        while (!socket.isOutputShutdown) {
            if (br.ready()) {
                println("Client start writing in channel...")
                Thread.sleep(1000)
                val clientCommand: String = br.readLine()

                dos.writeUTF(clientCommand)
                dos.flush()
                println("Client sent message $clientCommand to server")
                Thread.sleep(3000)

                if (clientCommand.equals("quit", ignoreCase = true)) {
                    println("Client kill connections")
                    Thread.sleep(2000)

                    if (dis.read() > -1) {
                        println("reading...")
                        val inStr: String = dis.readUTF()
                        println(inStr)
                    }
                    break
                }

                println("Шимонович Анастасия")
                println("${Calendar.getInstance().get(Calendar.DAY_OF_MONTH)}:${Calendar.getInstance().get(Calendar.MONTH)}:${Calendar.getInstance().get(Calendar.YEAR)}")

                println("Client sent message & start waiting for data from server...")
                Thread.sleep(2000)

                if (dis.read() > -1) {
                    println("reading...")
                    val inStr = dis.readUTF()
                    println(inStr)
                }
            }
        }
        println("Closing connections & channels on clentSide - DONE.")
    } catch (e: UnknownHostException) {
        e.printStackTrace()
    } catch (e: IOException) {
        e.printStackTrace()
    }
}