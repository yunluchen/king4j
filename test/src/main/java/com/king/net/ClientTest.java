package com.king.net;

import com.google.protobuf.ByteString;
import com.king.net.NetMessageProtos.PageRequest;
import com.king.net.NetMessageProtos.PageResult;
import com.king.net.NetMessageProtos.AccountRequest;
import com.king.net.NetMessageProtos.NutritionRequest;
import com.king.net.NetMessageProtos.HealthRequest;
import com.king.net.NetMessageProtos.DataRequest;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class ClientTest {

    private static final String SERVER_IP = "211.101.18.110";
    private static final int SERVER_PORT = 33477;
    private static final int BUFFER_SIZE = 1024 * 2;

    public static void main(String[] args) {

//        PageRequest pageRequest = PageRequest.newBuilder().setRequestId( 2 ).setUserId( 89 ).build();
        /*
        byte[] _username = "A".getBytes();
        byte[] _password = "B".getBytes();
        ByteString username = ByteString.copyFrom( _username );
        ByteString password = ByteString.copyFrom( _password );
        AccountRequest accountRequest = AccountRequest.newBuilder().setRequestId( 3 ).setUsername( username ).setPassword( password ).build();
        PageRequest pageRequest = PageRequest.newBuilder().setRequestId( 1 ).setUserId( 9 ).setAccountRequest( accountRequest ).build();
        */

        /*
        NutritionRequest nutritionRequest = NutritionRequest.newBuilder().setRequestId( 2 ).build();
        PageRequest pageRequest = PageRequest.newBuilder().setRequestId( 3 ).setUserId( 8 ).setNutritionRequest( nutritionRequest ).build();
        */

        /*
        HealthRequest healthRequest = HealthRequest.newBuilder().setRequestId( 3 ).setGender( 0 ).setIsKid( 0 ).build();
        PageRequest pageRequest = PageRequest.newBuilder().setRequestId( 4 ).setUserId( 7 ).setHealthRequest( healthRequest ).build();
        */

        DataRequest dataRequest = DataRequest.newBuilder().setRequestId( 2 ).build();
        PageRequest pageRequest = PageRequest.newBuilder().setRequestId( 5 ).setUserId( 6 ).setDataRequest( dataRequest ).build();

        byte[] buffer = pageRequest.toByteArray();
        PageResult pageResult = null;

        try {
            Socket socket = new Socket( SERVER_IP, SERVER_PORT );
            BufferedReader in = new BufferedReader( new InputStreamReader( socket.getInputStream() ) );
            socket.getOutputStream().write( buffer );

            socket.getOutputStream().flush();
            pageResult = PageResult.parseFrom( socket.getInputStream() );

            socket.getOutputStream().close();
//            socket.getInputStream().close();

        } catch ( IOException e ) {
            e.printStackTrace();
        }

        System.out.println( pageResult.toString() );
    }

}
