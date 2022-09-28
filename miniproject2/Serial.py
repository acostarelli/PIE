class Serial:
    def __init__(self, port=PORT, baud=BAUD, timeout=1000):
        self._port = port
        self._baud = baud
        self._timeout = timeout
        self._ser = None

        self._connect()

    def _connect(self):
        print("Connecting...")
        while True:
            try:
                self._ser = serial.Serial(self._port, self._baud, timeout=self._timeout)
            except Exception as e:
                print(time_ns(), e)
                pass
        print("done.")

    def readline(self):
        try:
            return self._ser.readline()
        except:
            self._connect()
            return self.read()

    def close(self):
        return self._ser.close()