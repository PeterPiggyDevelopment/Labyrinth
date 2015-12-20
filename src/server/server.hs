{-# LANGUAGE OverloadedStrings #-}
 
import Data.ByteString.Char8 ()
import System.Exit
import Network hiding (accept, sClose)
import Network.Socket hiding (recv)
import Network.Socket.ByteString (sendAll, recv)
import Control.Concurrent
 
main :: IO a
main = withSocketsDo $ do --forkIO comandListen
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
loop :: Socket -> IO b
loop sock = do
   (conn, _) <- accept sock
   _ <- forkIO $ body conn
   loop sock
   where
      body c = do
              line <- recv c 1024;
              print line
              sendAll c $ line
              sClose c
