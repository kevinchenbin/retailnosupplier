object frmorderimportselect: Tfrmorderimportselect
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #35746#21333#23548#20837#36873#25321
  ClientHeight = 428
  ClientWidth = 714
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 17
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 714
    Height = 428
    Align = alClient
    BevelInner = bvLowered
    ParentBackground = False
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 16
      Width = 48
      Height = 17
      Caption = #23458#25143#35746#20070
    end
    object SpeedButton1: TSpeedButton
      Left = 536
      Top = 399
      Width = 65
      Height = 22
      Caption = #30830#23450
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 631
      Top = 399
      Width = 65
      Height = 22
      Caption = #26032#24314#20070#30446
      OnClick = SpeedButton2Click
    end
    object Label2: TLabel
      Left = 368
      Top = 16
      Width = 36
      Height = 17
      Caption = #20986#29256#31038
    end
    object edbook: TEdit
      Left = 86
      Top = 13
      Width = 223
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 0
    end
    object DBGrid1: TDBGrid
      Left = 3
      Top = 42
      Width = 703
      Height = 354
      DataSource = ds
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      PopupMenu = pm
      TabOrder = 1
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'ISBN'
          Title.Alignment = taCenter
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Author'
          Title.Alignment = taCenter
          Title.Caption = #20316#32773
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PressCount'
          Title.Alignment = taCenter
          Title.Caption = #29256#27425
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'date'
          Title.Alignment = taCenter
          Title.Caption = #24405#20837' '#26085#26399
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Pressdate'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#26085#26399
          Width = 70
          Visible = True
        end>
    end
    object edpress: TEdit
      Left = 408
      Top = 13
      Width = 185
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 2
    end
    object buhebing: TButton
      Left = 631
      Top = 13
      Width = 75
      Height = 25
      Caption = #21512#24182
      TabOrder = 3
      OnClick = buhebingClick
    end
  end
  object query: TADOQuery
    Parameters = <>
    Left = 720
    Top = 8
  end
  object ds: TDataSource
    DataSet = query
    Left = 720
    Top = 56
  end
  object pm: TPopupMenu
    Left = 440
    Top = 176
    object N1: TMenuItem
      Caption = #35774#32622#20026#21512#24182#28304#20070#30446
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #35774#32622#20026#21512#24182#30446#26631#20070#30446
      OnClick = N2Click
    end
  end
  object comHebingshumu: TADOCommand
    CommandText = 'USP_BS_hebingbook;1'
    CommandType = cmdStoredProc
    Parameters = <
      item
        Name = '@ybookid'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@mbookid'
        DataType = ftInteger
        Size = 10
        Value = Null
      end>
    Left = 416
    Top = 88
  end
  object fcon: TADOConnection
    Left = 584
    Top = 168
  end
end
