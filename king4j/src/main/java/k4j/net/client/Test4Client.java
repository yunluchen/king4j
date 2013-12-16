package k4j.net.client;

import k4j.net.client.NetClient;
import k4j.net.client.NetClientFactory;
import k4j.net.client.NetClientHandler;

/**
 * Created by tom on 12/16/13.
 */
public class Test4Client {

    public static void main(String[] args) {
        NetClient netClient = NetClientFactory.createNetClient( "localhost", 33477 );
        netClient.setHandler( new NetClientHandler() {

            @Override
            public void receiveData(String data) {
                System.out.println(data);
            }

        } );
        netClient.send( "4test" );
    }

}
