object frmmembersearch: Tfrmmembersearch
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #35746#38405#26597#35810
  ClientHeight = 408
  ClientWidth = 488
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
    Width = 488
    Height = 408
    Align = alClient
    BevelInner = bvLowered
    Caption = 'Panel1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    ShowCaption = False
    TabOrder = 0
    object Label1: TLabel
      Left = 276
      Top = 73
      Width = 12
      Height = 17
      Caption = #21040
    end
    object dbgrid: TRzDBGrid
      Left = 5
      Top = 131
      Width = 474
      Height = 265
      DataSource = ds
      DefaultDrawing = True
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      TabOrder = 0
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      OnDblClick = dbgridDblClick
      Columns = <
        item
          Expanded = False
          FieldName = 'notecode'
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'membername'
          Title.Alignment = taCenter
          Title.Caption = #20250#21592
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'CardSN'
          Title.Alignment = taCenter
          Title.Caption = #20250#21592#21345#21495
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'hdtime'
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalAmount'
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalFixedPrice'
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalDiscountedprice'
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'username'
          Title.Alignment = taCenter
          Title.Caption = #25805#20316#21592
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'remarks'
          Title.Alignment = taCenter
          Title.Caption = #22791#27880
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 120
          Visible = True
        end>
    end
    object dtpstart: TDateTimePicker
      Left = 84
      Top = 8
      Width = 113
      Height = 25
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnChange = dtpstartChange
    end
    object chstart: TCheckBox
      Left = 9
      Top = 13
      Width = 74
      Height = 17
      Caption = #36215#22987#26102#38388
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object dtpend: TDateTimePicker
      Left = 360
      Top = 9
      Width = 119
      Height = 25
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnChange = dtpendChange
    end
    object chend: TCheckBox
      Left = 280
      Top = 13
      Width = 74
      Height = 17
      Caption = #32467#26463#26102#38388
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object chclient: TCheckBox
      Left = 9
      Top = 44
      Width = 65
      Height = 17
      Caption = #20250#21592
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 5
    end
    object edclient: TEdit
      Left = 84
      Top = 40
      Width = 109
      Height = 25
      AutoSize = False
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 6
      OnChange = edclientChange
      OnKeyPress = edclientKeyPress
    end
    object chcode: TCheckBox
      Left = 9
      Top = 71
      Width = 74
      Height = 17
      Caption = #21333#21495
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 7
    end
    object edcode: TEdit
      Left = 84
      Top = 70
      Width = 181
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      NumbersOnly = True
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 8
      OnChange = edcodeChange
    end
    object Button1: TButton
      Left = 312
      Top = 99
      Width = 75
      Height = 25
      Caption = #26597#35810
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 9
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 404
      Top = 100
      Width = 75
      Height = 25
      Caption = #36864#20986
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 10
      OnClick = Button2Click
    end
    object cbsupplier: TComboBox
      Left = 192
      Top = 40
      Width = 287
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ItemHeight = 17
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 11
    end
    object encodeend: TEdit
      Left = 298
      Top = 71
      Width = 181
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      NumbersOnly = True
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 12
    end
  end
  object aqquery: TADOQuery
    Parameters = <>
    Left = 272
    Top = 272
  end
  object ds: TDataSource
    DataSet = aqquery
    Left = 80
    Top = 256
  end
  object fcn: TADOConnection
    LoginPrompt = False
    Left = 336
    Top = 312
  end
end
