package k4j.net.server.inner;

import k4j.net.server.NetServer;
import k4j.net.server.NetServerHandler;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created by tom on 12/16/13.
 */
public class NetServerImpl
        implements NetServer {

    private Logger logger = LoggerFactory.getLogger( NetServer.class );
    private final int serverPort;
    private NetServerHandler netServerHandler;

    public NetServerImpl(int serverPort) {
        this.serverPort = serverPort;
    }

    @Override
    public void setHandler(NetServerHandler netServerHandler) {
        this.netServerHandler = netServerHandler;
    }

    @Override
    public void service() {
        if ( netServerHandler == null ) {
            logger.error( "not set NetServerHandler" );
            return;
        }
        try {
            wait4ComingClient();
        } catch ( IOException e ) {
            logger.error( e.toString() );
        }
    }

    private void wait4ComingClient() throws IOException {
        logger.info( "server start" );
        ServerSocket serverSocket = new ServerSocket( serverPort );
        while ( true ) {
            Socket socket = serverSocket.accept();
            logger.info( "accept " + socket.getInetAddress() + " @ " + socket.getPort() );
            BufferedReader br = getReader( socket );
            PrintWriter pw = getWriter( socket );
            StringBuffer data = new StringBuffer();
            String msg;
            while ( ( msg = br.readLine() ) != null )
                data.append( msg );
            socket.shutdownInput();
            pw.println( netServerHandler.returnByReceiveData( data.toString() ) );
            if ( socket != null ) {
                logger.info( "close " + socket.getInetAddress() + " @ " + socket.getPort() );
                socket.close();
            }

        }
    }

    @Override
    public void stop() {

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
