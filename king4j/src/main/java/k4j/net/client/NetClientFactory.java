package k4j.net.client;

import k4j.net.client.inner.NetClientImpl;

/**
 * Created by tom on 12/16/13.
 */
public class NetClientFactory {

    public static NetClient createNetClient(String serverIP, int serverPort){
        return new NetClientImpl(serverIP, serverPort);
    }

}
