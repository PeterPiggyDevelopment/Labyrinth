{-# LANGUAGE ForeignFunctionInterface #-}
 
import Data.ByteString.Char8 (pack,  unpack)
import Network hiding (accept, sClose)
import Network.Socket hiding (recv)
import Network.Socket.ByteString (sendAll, recv)
import Control.Concurrent
import Foreign.C
import Foreign.Marshal.Alloc()

foreign import ccall start_finding:: CString -> CString
 
main :: IO a
main = withSocketsDo (listenOn (PortNumber 5002) >>= loop)

loop :: Socket -> IO b
loop sock = do
   (conn, _) <- accept sock
   _ <- forkIO $ body conn
   loop sock
   where
      body conn = do
              line <- start_finding <$> (( unpack <$> recv conn 1024) >>= newCString)
              lint <- pack <$> peekCString line
              sendAll conn lint 
              sClose conn
