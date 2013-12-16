package k4j.net.client.inner;

import k4j.net.client.NetClient;
import k4j.net.client.NetClientHandler;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.net.Socket;

/**
 * Created by tom on 12/16/13.
 */
public class NetClientImpl implements NetClient {

    private Logger logger = LoggerFactory.getLogger( NetClient.class );
    private final String serverIP;
    private final int serverPort;
    private NetClientHandler netClientHandler;

    public NetClientImpl(String serverIP, int serverPort) {
        this.serverIP = serverIP;
        this.serverPort = serverPort;
    }

    @Override
    public void setHandler(NetClientHandler netClientHandler) {
        this.netClientHandler = netClientHandler;
    }

    @Override
    public void send(String value) {
        if (netClientHandler == null){
            logger.error( "not set NetClientHandler" );
            return;
        }
        try {
            send2Server( value );
        } catch ( IOException e ) {
            logger.error( e.toString() );
        }

    }

    private void send2Server(String value) throws IOException {
        Socket socket = new Socket(serverIP, serverPort);
        BufferedReader br = getReader( socket );
        PrintWriter pw = getWriter( socket );
        pw.write( value );
        pw.flush();
        socket.shutdownOutput();
        StringBuffer data = new StringBuffer();
        String msg;
        while ( ( msg = br.readLine() ) != null )
            data.append( msg );
        netClientHandler.receiveData( data.toString() );
        socket.close();
    }

    private PrintWriter getWriter(Socket socket) throws IOException {
        OutputStream socketOut = socket.getOutputStream();
        return new PrintWriter( socketOut, true );
    }

    private BufferedReader getReader(Socket socket) throws IOException {
        InputStream socketIn = socket.getInputStream();
        return new BufferedReader( new InputStreamReader( socketIn ) );
    }

}
