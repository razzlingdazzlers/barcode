class BarCode
  ENCODING = [ # ascii 32 -> 0
    212222, 222122, 222221, 121223, 121322, 131222, 122213, 122312, 132212,
    221213, 221312, 231212, 112232, 122132, 122231, 113222, 123122, 123221,
    223211, 221132, 221231, 213212, 223112, 312131, 311222, 321122, 321221,
    312212, 322112, 322211, 212123, 212321, 232121, 111323, 131123, 131321,
    112313, 132113, 132311, 211313, 231113, 231311, 112133, 112331, 132131,
    113123, 113321, 133121, 313121, 211331, 231131, 213113, 213311, 213131,
    311123, 311321, 331121, 312113, 312311, 332111, 314111, 221411, 431111,
    111224, 111422, 121124, 121421, 141122, 141221, 112214, 112412, 122114,
    122411, 142112, 142211, 241211, 221114, 413111, 241112, 134111, 111242,
    121142, 121241, 114212, 124112, 124211, 411212, 421112, 421211, 212141,
    214121, 412121, 111143, 111341, 131141, 114113, 114311, 411113, 411311,
    113141, 114131, 311141, 411131, 211412, 211214, 211232, 2331112,
  ]

  START_A = 103
  START_B = 104
  START_C = 105
  SHIFT   = 98
  CODE_A  = 101
  CODE_B  = 100
  CODE_C  = 99
  STOP    = 106
  FNC_1   = 102
  FNC_2   = 97
  FNC_3   = 96

  def initialize(data)
    @bar_widths = [ENCODING[START_A]]

    position = 1
    @sum = 0
    data.unpack("c*").each do |c|
      @sum += position * (c - 32)
      position += 1
      @bar_widths << encoding_for(c)
    end

    @sum %= 103

    @bar_widths << ENCODING[@sum]
    @bar_widths << ENCODING[STOP]
  end

  def render
    "".tap do |o|
      black = true
      @bar_widths.each do |v|
        v.to_s.unpack("c*").map(&:chr).map(&:to_i).each do |n|
          n.times do
            o << "<div class=\"#{black ? :black : :white}\"></div>"
          end
          black = !black
        end
      end
    end
  end

  def encoding_for(c)
    ENCODING[c - 32]
  end
end

bc = BarCode.new('PJJ123C')

html = "
<html>
<head>
  <style>
    * {
      margin:0px;
      border:0px;
      padding:0px;
    }

    body {
      padding: 50px;
    }

    div {
      width: 2px;
      height: 100px;
      display: inline-block;
    }

    .black {
      background-color: black;
    }
  </style>
</head>
<body>
  #{bc.render}
</body>
</html>
"

File.open("index.html", 'w') { |f| f.write(html) }

