object frmcaigouquery: Tfrmcaigouquery
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #26597#21333
  ClientHeight = 442
  ClientWidth = 580
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 580
    Height = 442
    Align = alClient
    BevelInner = bvLowered
    ParentBackground = False
    TabOrder = 0
    object dtpstart: TDateTimePicker
      Left = 84
      Top = 5
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
      TabOrder = 0
      OnChange = dtpstartChange
    end
    object chstart: TCheckBox
      Left = 4
      Top = 9
      Width = 74
      Height = 17
      Caption = #36215#22987#26102#38388
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object dtpend: TDateTimePicker
      Left = 451
      Top = 5
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
      TabOrder = 2
      OnChange = dtpendChange
    end
    object chend: TCheckBox
      Left = 368
      Top = 9
      Width = 74
      Height = 17
      Caption = #32467#26463#26102#38388
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object chclient: TCheckBox
      Left = 4
      Top = 38
      Width = 65
      Height = 17
      Caption = #20379#24212#21830
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object edclient: TEdit
      Left = 84
      Top = 34
      Width = 73
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
      TabOrder = 5
      OnKeyPress = edclientKeyPress
    end
    object chcode: TCheckBox
      Left = 4
      Top = 64
      Width = 74
      Height = 17
      Caption = #21333#21495
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 6
    end
    object edcode: TEdit
      Left = 84
      Top = 61
      Width = 485
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
      TabOrder = 7
      OnChange = edcodeChange
    end
    object DBGrid1: TDBGrid
      Left = 1
      Top = 118
      Width = 569
      Height = 320
      Ctl3D = False
      DataSource = ds
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentCtl3D = False
      ParentFont = False
      PopupMenu = PopupMenu1
      TabOrder = 8
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      OnDblClick = DBGrid1DblClick
      OnKeyPress = DBGrid1KeyPress
      Columns = <
        item
          Expanded = False
          FieldName = 'clientname'
          Title.Alignment = taCenter
          Title.Caption = #20379#24212#21830#21517#31216
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'NtCode'
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalAmount'
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'FixedPrice'
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'DiscountedPrice'
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'remarks'
          Title.Alignment = taCenter
          Title.Caption = #22791#27880
          Width = 90
          Visible = True
        end>
    end
    object Button1: TButton
      Left = 416
      Top = 87
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
      Left = 494
      Top = 87
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
      Left = 156
      Top = 34
      Width = 413
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
      OnChange = cbsupplierChange
    end
    object cbyangshu: TCheckBox
      Left = 4
      Top = 91
      Width = 65
      Height = 17
      Caption = #31867#22411
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 12
      Visible = False
    end
    object cbrukuleixing: TComboBox
      Left = 84
      Top = 87
      Width = 113
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ItemHeight = 17
      ItemIndex = 0
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 13
      Text = #19968#33324#20837#24211
      Visible = False
      OnChange = cbrukuleixingChange
      Items.Strings = (
        #19968#33324#20837#24211
        #26679#20070#20837#24211)
    end
    object editbk: TEdit
      Left = 84
      Top = 88
      Width = 229
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 14
      Visible = False
      OnChange = editbkChange
    end
    object cbrkbz: TCheckBox
      Left = 222
      Top = 90
      Width = 46
      Height = 17
      Caption = #22791#27880
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 15
      Visible = False
    end
    object editrkbk: TEdit
      Left = 274
      Top = 88
      Width = 97
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 16
      Text = #28100#21338#21040#36135
      Visible = False
      OnChange = editrkbkChange
    end
  end
  object fcon: TADOConnection
    Left = 192
    Top = 192
  end
  object ds: TDataSource
    DataSet = query
    Left = 336
    Top = 184
  end
  object query: TADOQuery
    Parameters = <>
    Left = 376
    Top = 288
  end
  object PopupMenu1: TPopupMenu
    Left = 296
    Top = 304
    object N1: TMenuItem
      Caption = #26356#26032#22791#27880
      OnClick = N1Click
    end
  end
end
