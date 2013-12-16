package k4j.net.server;

import k4j.net.server.NetServerHandler;
import k4j.net.server.NetServer;
import k4j.net.server.NetServerFactory;

/**
 * Created by tom on 12/16/13.
 */
public class Test4Server {

    public static void main(String[] args) {
        NetServer netServer = NetServerFactory.createNetServer( 33477 );
        netServer.setHandler( new NetServerHandler() {

            @Override
            public String returnByReceiveData(String data) {
                System.out.println(data);
                return data;
            }

        } );
        netServer.service();
    }

}
