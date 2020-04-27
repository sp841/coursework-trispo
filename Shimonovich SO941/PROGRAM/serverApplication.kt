import java.io.DataInputStream
import java.io.DataOutputStream
import java.io.IOException
import java.net.ServerSocket
import java.util.*

fun main(args: Array<String>) {
    val serverSocket = ServerSocket(3345)
    val parser: ExpressionParser = ExpressionParser()
    try {
        val client = serverSocket.accept()

        println("Connection accept")

        val out: DataOutputStream = DataOutputStream(client.getOutputStream())
        println("DataOutputStream created")

        val inputStream: DataInputStream = DataInputStream(client.getInputStream())
        println("DataInputStream created")

        while (!client.isClosed) {
            println("Server reading from chanel")

            println()

            println("Шимонович Анастасия")
            println("${Calendar.getInstance().get(Calendar.DAY_OF_MONTH)}:${Calendar.getInstance().get(Calendar.MONTH)}:${Calendar.getInstance().get(Calendar.YEAR)}")

            var entry: String = ""
            entry = inputStream.readUTF()
            println("READ from client message - $entry")
            println("Server try writing to chanel")

            val expression: List<String> = ExpressionParser.parse(entry)
            var flag: Boolean = ExpressionParser.flag

            if (entry.equals("quit", ignoreCase = true)) {
                println("Client initialize connections suicide ...")
                out.writeUTF("Server reply - $entry - OK")
                out.flush()
                Thread.sleep(3000)
                break
            }

            out.writeBoolean(true)
//            out.writeUTF("Server reply - ${entry.toUpperCase()} - OK")
            out.writeUTF("Answer: ${Ideon.calc(expression)}")
            println("Server Wrote message to client.")

            out.flush()
        }

        println("Client disconnect")
        println("Closing connections & channels")

        inputStream.close()
        out.close()

        client.close()

        println("Closing connections & channels - DONE.")
    } catch (e: IOException) {
        e.printStackTrace()
    }
}