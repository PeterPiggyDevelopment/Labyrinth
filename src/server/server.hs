{-# LANGUAGE OverloadedStrings #-}
 
import Data.ByteString.Char8 hiding (getLine, putStrLn)
import System.Exit
import Network hiding (accept, sClose)
import Network.Socket hiding (recv)
import Network.Socket.ByteString (sendAll, recv)
import Control.Concurrent
 
main = withSocketsDo $ do
    --forkIO comandListen
    sock <- listenOn $ PortNumber 5002
    loop sock
    where
        comandListen = do
            com <- getLine
            if com == "exit" then exitSuccess
            else do 
                putStrLn "Invalid Invalidovich"
                comandListen
 
{-# INLINE loop #-}
loop sock = do
   (conn, _) <- accept sock
   forkIO $ body conn
   loop sock
   where
      body c = do 
              line <- recv c 1024;
              print line
              sendAll c $ line
              sClose c
