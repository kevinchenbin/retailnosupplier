object frmprintbag: Tfrmprintbag
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #21333#20070#25171#21253#35774#32622
  ClientHeight = 409
  ClientWidth = 350
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 350
    Height = 409
    Align = alClient
    BevelInner = bvLowered
    ParentBackground = False
    TabOrder = 0
    object DBGrid1: TDBGrid
      Left = 2
      Top = 2
      Width = 346
      Height = 330
      Align = alTop
      Ctl3D = False
      DataSource = ds
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'name'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Amount'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Width = 35
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'BookWords'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #20876'/'#21253
          Width = 35
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'printbag'
          Title.Alignment = taCenter
          Title.Caption = #27599#21253#20876#25968
          Width = 50
          Visible = True
        end>
    end
    object RzButton1: TRzButton
      Left = 262
      Top = 342
      Caption = #30830#23450
      TabOrder = 1
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 262
      Top = 373
      Caption = #21462#28040
      TabOrder = 2
      OnClick = RzButton2Click
    end
    object RzButton3: TRzButton
      Tag = 1
      Left = 16
      Top = 342
      Caption = #25171#21253#21333#39044#35272
      TabOrder = 3
      OnClick = RzButton3Click
    end
    object RzButton4: TRzButton
      Tag = 2
      Left = 16
      Top = 373
      Caption = #25171#21360#25171#21253#21333
      TabOrder = 4
      OnClick = RzButton3Click
    end
  end
  object fcon: TADOConnection
    Left = 320
    Top = 40
  end
  object ImageList1: TImageList
    Left = 320
    Top = 88
    Bitmap = {
      494C010102000800240010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      9900000099000000990000009900000099000000990000009900000099000000
      9900000099000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099000000
      CC000000CC000000CC000000CC000000CC00000099000000CC00000099000000
      990000009900000099000000000000000000000000000000000099999900B2B2
      B200B2B2B200B2B2B200B2B2B200B2B2B20099999900B2B2B200999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099000000
      FF000000CC000000CC000000CC000000CC000000CC00000099000000CC000000
      990000009900000099000000000000000000000000000000000099999900CCCC
      CC00B2B2B200B2B2B200B2B2B200B2B2B200B2B2B20099999900B2B2B2009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099000000
      CC000000FF000000CC000000CC000000CC000000CC000000CC00000099000000
      CC0000009900000099000000000000000000000000000000000099999900B2B2
      B200CCCCCC00B2B2B200B2B2B200B2B2B200B2B2B200B2B2B20099999900B2B2
      B200999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099000000
      FF000000CC000000FF000000CC000000CC000000CC000000CC000000CC000000
      99000000CC00000099000000000000000000000000000000000099999900CCCC
      CC00B2B2B200CCCCCC00B2B2B200B2B2B200B2B2B200B2B2B200B2B2B2009999
      9900B2B2B2009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099000000
      FF000000FF000000CC000000FF000000CC000000CC000000CC000000CC000000
      CC0000009900000099000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00B2B2B200CCCCCC00B2B2B200B2B2B200B2B2B200B2B2B200B2B2
      B200999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099009999
      FF000000FF000000FF000000CC000000FF000000CC000000CC000000CC000000
      CC000000CC00000099000000000000000000000000000000000099999900E5E5
      E500CCCCCC00CCCCCC00B2B2B200CCCCCC00B2B2B200B2B2B200B2B2B200B2B2
      B200B2B2B2009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099009999
      FF009999FF000000FF000000FF000000CC000000FF000000CC000000CC000000
      CC000000CC00000099000000000000000000000000000000000099999900E5E5
      E500E5E5E500CCCCCC00CCCCCC00B2B2B200CCCCCC00B2B2B200B2B2B200B2B2
      B200B2B2B2009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      9900000099000000990000009900000099000000990000009900000099000000
      9900000099000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFF00000000FFFFFFFF00000000
      FFFFFFFF00000000FFFFFFFF00000000E007E00700000000C003C00300000000
      C003C00300000000C003C00300000000C003C00300000000C003C00300000000
      C003C00300000000C003C00300000000E007E00700000000FFFFFFFF00000000
      FFFFFFFF00000000FFFFFFFF0000000000000000000000000000000000000000
      000000000000}
  end
  object query: TADOQuery
    Parameters = <>
    Left = 256
    Top = 48
  end
  object ds: TDataSource
    DataSet = query
    Left = 120
    Top = 152
  end
  object spdabao: TADOStoredProc
    ProcedureName = 'DaBaoA'
    Parameters = <
      item
        Name = '@DanHaoID'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@CatalogiD'
        DataType = ftString
        Size = -1
        Value = Null
      end
      item
        Name = '@xuhaostr'
        DataType = ftString
        Size = -1
        Value = Null
      end
      item
        Name = '@userid'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@stgid'
        DataType = ftInteger
        Value = Null
      end>
    Left = 56
    Top = 232
  end
  object rp: TRvProject
    Engine = rs
    Left = 192
    Top = 344
  end
  object rv: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = querydabao
    Left = 136
    Top = 352
  end
  object querydabao: TADOQuery
    AutoCalcFields = False
    CursorType = ctStatic
    Parameters = <>
    Left = 216
    Top = 224
  end
  object rs: TRvSystem
    TitleSetup = 'Output Options'
    TitleStatus = 'Report Status'
    TitlePreview = 'Report Preview'
    SystemFiler.StatusFormat = 'Generating page %p'
    SystemPreview.ZoomFactor = 100.000000000000000000
    SystemPrinter.ScaleX = 100.000000000000000000
    SystemPrinter.ScaleY = 100.000000000000000000
    SystemPrinter.StatusFormat = 'Printing page %p'
    SystemPrinter.Title = 'Rave Report'
    SystemPrinter.UnitsFactor = 1.000000000000000000
    Left = 120
    Top = 280
  end
end
