{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE ForeignFunctionInterface #-}
 
import Data.ByteString.Char8 (pack,  unpack)
import System.Exit
import Network hiding (accept, sClose)
import Network.Socket hiding (recv)
import Network.Socket.ByteString (sendAll, recv)
import Control.Concurrent
import Foreign.C
import Foreign.Marshal.Alloc

foreign import ccall start_finding:: CString -> CString
 
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
      body conn = do
              line <- start_finding <$> (( unpack <$> (recv conn 1024)) >>= (newCString))
              lint <- pack <$> peekCString line
              print lint
              sendAll conn $ lint 
              free line
              sClose conn
